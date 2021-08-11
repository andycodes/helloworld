static ssize_t show_target_loads(struct cpufreq_interactive_tunables *tunables, char *buf)
{
	int i;
	ssize_t ret = 0;
	unsigned long flags;
 
	spin_lock_irqsave(&tunables->target_loads_lock, flags);
 
	// 多个load之间使用:隔开
	for (i = 0; i < tunables->ntarget_loads; i++)
		ret += sprintf(buf + ret, "%u%s", tunables->target_loads[i], i & 0x1 ? ":" : " ");
 
	sprintf(buf + ret - 1, "\n");
	spin_unlock_irqrestore(&tunables->target_loads_lock, flags);
	return ret;
}
 
static ssize_t store_target_loads(struct cpufreq_interactive_tunables *tunables, const char *buf, size_t count)
{
	int ntokens;
	unsigned int *new_target_loads = NULL;
	unsigned long flags;
 
	new_target_loads = get_tokenized_data(buf, &ntokens);
	if (IS_ERR(new_target_loads))
		return PTR_RET(new_target_loads);
 
	spin_lock_irqsave(&tunables->target_loads_lock, flags);
	if (tunables->target_loads != default_target_loads){
		kfree(tunables->target_loads);
	}
	tunables->target_loads = new_target_loads;
	tunables->ntarget_loads = ntokens;
	spin_unlock_irqrestore(&tunables->target_loads_lock, flags);
	return count;
}
 
// 存储timer_slack
static ssize_t store_timer_slack(struct cpufreq_interactive_tunables *tunables,
		const char *buf, size_t count)
{
	int ret;
	unsigned long val;
 
	ret = kstrtol(buf, 10, &val);
	if (ret < 0)
		return ret;
 
	tunables->timer_slack_val = val;
	return count;
}
 
static ssize_t store_timer_rate(struct cpufreq_interactive_tunables *tunables, const char *buf, size_t count)
{
	int ret;
	unsigned long val, val_round;
 
	ret = kstrtoul(buf, 0, &val);
	if (ret < 0)
		return ret;
 
	val_round = jiffies_to_usecs(usecs_to_jiffies(val));
	// 还是转换成内核jiffies时间
	if (val != val_round)
		pr_warn("timer_rate not aligned to jiffy. Rounded up to %lu\n",val_round);
 
	tunables->timer_rate = val_round;
	return count;
}
 
// 维持在boost的最短时间
static ssize_t show_boostpulse_duration(struct cpufreq_interactive_tunables *tunables, char *buf)
{
	return sprintf(buf, "%d\n", tunables->boostpulse_duration_val);
}
 
static ssize_t store_boostpulse_duration(struct cpufreq_interactive_tunables *tunables, const char *buf, size_t count)
{
	int ret;
	unsigned long val;
 
	// 将char ×转换成 unsigned long类型
	ret = kstrtoul(buf, 0, &val);
	if (ret < 0)
		return ret;
 
	tunables->boostpulse_duration_val = val;
	return count;
}
static ssize_t store_boost(struct cpufreq_interactive_tunables *tunables, const char *buf, size_t count)
{
	int ret;
	unsigned long val;
 
	ret = kstrtoul(buf, 0, &val);
	if (ret < 0)
		return ret;
 
	tunables->boost_val = val;
 
	// 打开boost模式
	if (tunables->boost_val) {
		trace_cpufreq_interactive_boost("on");
		if (!tunables->boosted){
			// 这里是boost失败，则进行下面处理
			cpufreq_interactive_boost(tunables);
		}
	// 关闭boost模式
	} else {
		tunables->boostpulse_endtime = ktime_to_us(ktime_get());
		trace_cpufreq_interactive_unboost("off");
	}
 
	return count;
}
 
// 直接将freq调整到hispeed_freq
static void cpufreq_interactive_boost(struct cpufreq_interactive_tunables *tunables)
{
	int i;
	int anyboost = 0;
	unsigned long flags[2];
	struct cpufreq_interactive_cpuinfo *pcpu;
 
	tunables->boosted = true;
 
	spin_lock_irqsave(&speedchange_cpumask_lock, flags[0]);
 
	for_each_online_cpu(i) {
		pcpu = &per_cpu(cpuinfo, i);
 
		if (!down_read_trylock(&pcpu->enable_sem))
			continue;
 
		if (!pcpu->governor_enabled) {
			up_read(&pcpu->enable_sem);
			continue;
		}
 
		if (tunables != pcpu->policy->governor_data) {
			up_read(&pcpu->enable_sem);
			continue;
		}
 
		spin_lock_irqsave(&pcpu->target_freq_lock, flags[1]);
		if (pcpu->target_freq < tunables->hispeed_freq) {
			pcpu->target_freq = tunables->hispeed_freq;
			cpumask_set_cpu(i, &speedchange_cpumask);
			pcpu->pol_hispeed_val_time = ktime_to_us(ktime_get());
			anyboost = 1;
		}
		spin_unlock_irqrestore(&pcpu->target_freq_lock, flags[1]);
 
		up_read(&pcpu->enable_sem);
	}
 
	spin_unlock_irqrestore(&speedchange_cpumask_lock, flags[0]);
 
	// 实际上就是唤醒这个线程去改变他的freq
	if (anyboost){
		wake_up_process(speedchange_task);
	}
}
 
static ssize_t store_hispeed_freq(struct cpufreq_interactive_tunables *tunables,
		const char *buf, size_t count)
{
	int ret;
	long unsigned int val;
 
	ret = kstrtoul(buf, 0, &val);
	if (ret < 0)
		return ret;
	tunables->hispeed_freq = val;
	return count;
}
 
static ssize_t store_go_hispeed_load(struct cpufreq_interactive_tunables
		*tunables, const char *buf, size_t count)
{
	int ret;
	unsigned long val;
 
	ret = kstrtoul(buf, 0, &val);
	if (ret < 0)
		return ret;
	tunables->go_hispeed_load = val;
	return count;
}
 
// 开始降频的最小时间
static ssize_t store_min_sample_time(struct cpufreq_interactive_tunables *tunables, const char *buf, size_t count)
{
	int ret;
	unsigned long val;
 
	ret = kstrtoul(buf, 0, &val);
	if (ret < 0)
		return ret;
	tunables->min_sample_time = val;
	return count;
}
 
static ssize_t show_above_hispeed_delay(
	struct cpufreq_interactive_tunables *tunables, char *buf)
{
	int i;
	ssize_t ret = 0;
	unsigned long flags;
 
	spin_lock_irqsave(&tunables->above_hispeed_delay_lock, flags);
 
	for (i = 0; i < tunables->nabove_hispeed_delay; i++)
		ret += sprintf(buf + ret, "%u%s", tunables->above_hispeed_delay[i], i & 0x1 ? ":" : " ");
 
	sprintf(buf + ret - 1, "\n");
	spin_unlock_irqrestore(&tunables->above_hispeed_delay_lock, flags);
	return ret;
}
 
static ssize_t store_above_hispeed_delay( struct cpufreq_interactive_tunables *tunables, const char *buf, size_t count)
{
	int ntokens;
	unsigned int *new_above_hispeed_delay = NULL;
	unsigned long flags;
 
	new_above_hispeed_delay = get_tokenized_data(buf, &ntokens);
	if (IS_ERR(new_above_hispeed_delay))
		return PTR_RET(new_above_hispeed_delay);
 
	spin_lock_irqsave(&tunables->above_hispeed_delay_lock, flags);
	if (tunables->above_hispeed_delay != default_above_hispeed_delay)
		kfree(tunables->above_hispeed_delay);
	tunables->above_hispeed_delay = new_above_hispeed_delay;
	tunables->nabove_hispeed_delay = ntokens;
	spin_unlock_irqrestore(&tunables->above_hispeed_delay_lock, flags);
	return count;
 
}
 
 
常用的就是将字符串转换成int类型的一个函数
static unsigned int *get_tokenized_data(const char *buf, int *num_tokens)
{
	const char *cp;
	int i;
	int ntokens = 1;
	unsigned int *tokenized_data;
	int err = -EINVAL;
 
	cp = buf;
	//比较字符串str1和str2中是否有相同的字符，如果有，则返回该字符在str1中的位置的指针。
	while ((cp = strpbrk(cp + 1, " :")))
		ntokens++;
 
	if (!(ntokens & 0x1))
		goto err;
 
	tokenized_data = kmalloc(ntokens * sizeof(unsigned int), GFP_KERNEL);
	if (!tokenized_data) {
		err = -ENOMEM;
		goto err;
	}
 
	cp = buf;
	i = 0;
	while (i < ntokens) {
		if (sscanf(cp, "%u", &tokenized_data[i++]) != 1)
			goto err_kfree;
 
		cp = strpbrk(cp, " :");
		if (!cp)
			break;
		cp++;
	}
 
	if (i != ntokens)
		goto err_kfree;
 
	*num_tokens = ntokens;
	return tokenized_data;
 
err_kfree:
	kfree(tokenized_data);
err:
	return ERR_PTR(err);
}
 
// 这个是在核心层的回调函数，响应Init事件时使用
static struct attribute_group *get_sysfs_attr(void)
{
	if (have_governor_per_policy())
		return &interactive_attr_group_gov_pol;
	else
		return &interactive_attr_group_gov_sys;
}
/* Per policy governor instance */
static struct attribute *interactive_attributes_gov_pol[] = {
	&target_loads_gov_pol.attr,
	&above_hispeed_delay_gov_pol.attr,
	&hispeed_freq_gov_pol.attr,
	&go_hispeed_load_gov_pol.attr,
	&min_sample_time_gov_pol.attr,
	&timer_rate_gov_pol.attr,
	&timer_slack_gov_pol.attr,
	&boost_gov_pol.attr,
	&boostpulse_gov_pol.attr,
	&boostpulse_duration_gov_pol.attr,
	&io_is_busy_gov_pol.attr,
	NULL,
};
static struct attribute_group interactive_attr_group_gov_pol = {
	.attrs = interactive_attributes_gov_pol,
	.name = "interactive",
};
 
/*
 * Create show/store routines
 * - sys: One governor instance for complete SYSTEM
 * - pol: One governor instance per struct cpufreq_policy
 */
#define show_gov_pol_sys(file_name)					\
static ssize_t show_##file_name##_gov_sys				\
(struct kobject *kobj, struct attribute *attr, char *buf)		\
{									\
	return show_##file_name(common_tunables, buf);			\
}									\
									\
static ssize_t show_##file_name##_gov_pol				\
(struct cpufreq_policy *policy, char *buf)				\
{									\
	return show_##file_name(policy->governor_data, buf);		\
}
 
#define store_gov_pol_sys(file_name)					\
static ssize_t store_##file_name##_gov_sys				\
(struct kobject *kobj, struct attribute *attr, const char *buf,		\
	size_t count)							\
{									\
	return store_##file_name(common_tunables, buf, count);		\
}									\
									\
static ssize_t store_##file_name##_gov_pol				\
(struct cpufreq_policy *policy, const char *buf, size_t count)		\
{									\
	return store_##file_name(policy->governor_data, buf, count);	\
}
 
#define show_store_gov_pol_sys(file_name)				\
show_gov_pol_sys(file_name);						\
store_gov_pol_sys(file_name)
 
show_store_gov_pol_sys(target_loads);
show_store_gov_pol_sys(above_hispeed_delay);
show_store_gov_pol_sys(hispeed_freq);
show_store_gov_pol_sys(go_hispeed_load);
show_store_gov_pol_sys(min_sample_time);
show_store_gov_pol_sys(timer_rate);
show_store_gov_pol_sys(timer_slack);
show_store_gov_pol_sys(boost);
store_gov_pol_sys(boostpulse);
show_store_gov_pol_sys(boostpulse_duration);
show_store_gov_pol_sys(io_is_busy);
 
 
 
 
/* One Governor instance for entire system */
static struct attribute *interactive_attributes_gov_sys[] = {
	&target_loads_gov_sys.attr,
	&above_hispeed_delay_gov_sys.attr,
	&hispeed_freq_gov_sys.attr,
	&go_hispeed_load_gov_sys.attr,
	&min_sample_time_gov_sys.attr,
	&timer_rate_gov_sys.attr,
	&timer_slack_gov_sys.attr,
	&boost_gov_sys.attr,
	&boostpulse_gov_sys.attr,
	&boostpulse_duration_gov_sys.attr,
	&io_is_busy_gov_sys.attr,
	NULL,
};
 
static struct attribute_group interactive_attr_group_gov_sys = {
	.attrs = interactive_attributes_gov_sys,
	.name = "interactive",
};
 
#define gov_sys_attr_rw(_name)						\
static struct global_attr _name##_gov_sys =				\
__ATTR(_name, 0644, show_##_name##_gov_sys, store_##_name##_gov_sys)
 
#define gov_pol_attr_rw(_name)						\
static struct freq_attr _name##_gov_pol =				\
__ATTR(_name, 0644, show_##_name##_gov_pol, store_##_name##_gov_pol)
 
#define gov_sys_pol_attr_rw(_name)					\
	gov_sys_attr_rw(_name);						\
	gov_pol_attr_rw(_name)
 
gov_sys_pol_attr_rw(target_loads);
gov_sys_pol_attr_rw(above_hispeed_delay);
gov_sys_pol_attr_rw(hispeed_freq);
gov_sys_pol_attr_rw(go_hispeed_load);
gov_sys_pol_attr_rw(min_sample_time);
gov_sys_pol_attr_rw(timer_rate);
gov_sys_pol_attr_rw(timer_slack);
gov_sys_pol_attr_rw(boost);
gov_sys_pol_attr_rw(boostpulse_duration);
gov_sys_pol_attr_rw(io_is_busy);
 
 
 
boostpluse虽然这个节点不存在：
也就是没有去创建这个节点
static ssize_t store_boostpulse(struct cpufreq_interactive_tunables *tunables, const char *buf, size_t count)
{
	int ret;
	unsigned long val;
 
	ret = kstrtoul(buf, 0, &val);
	if (ret < 0)
		return ret;
 
	tunables->boostpulse_endtime = ktime_to_us(ktime_get()) + tunables->boostpulse_duration_val;
	trace_cpufreq_interactive_boost("pulse");
	if (!tunables->boosted)
		cpufreq_interactive_boost(tunables);
	return count;
}
 
static struct global_attr boostpulse_gov_sys =
	__ATTR(boostpulse, 0200, NULL, store_boostpulse_gov_sys);
 
static struct freq_attr boostpulse_gov_pol =
	__ATTR(boostpulse, 0200, NULL, store_boostpulse_gov_pol);


// 应急反应机制里面瞬间升高到的freq
static ssize_t show_hispeed_freq(struct cpufreq_interactive_tunables *tunables,
		char *buf)
{
	return sprintf(buf, "%u\n", tunables->hispeed_freq);
}
 
// 搞负载阈值
static ssize_t show_go_hispeed_load(struct cpufreq_interactive_tunables
		*tunables, char *buf)
{
	return sprintf(buf, "%lu\n", tunables->go_hispeed_load);
}
 
// cpu两次将频之间的时间间隔
static ssize_t show_min_sample_time(struct cpufreq_interactive_tunables
		*tunables, char *buf)
{
	return sprintf(buf, "%lu\n", tunables->min_sample_time);
}
 
// 采样频率
static ssize_t show_timer_rate(struct cpufreq_interactive_tunables *tunables,
		char *buf)
{
	return sprintf(buf, "%lu\n", tunables->timer_rate);
}
// 进入idle状态的定时器延迟
static ssize_t show_timer_slack(struct cpufreq_interactive_tunables *tunables,
		char *buf)
{
	return sprintf(buf, "%d\n", tunables->timer_slack_val);
}
 
// 是否根据io的负载来提升freq
static ssize_t show_io_is_busy(struct cpufreq_interactive_tunables *tunables,
		char *buf)
{
	return sprintf(buf, "%u\n", tunables->io_is_busy);
}
static ssize_t store_io_is_busy(struct cpufreq_interactive_tunables *tunables, const char *buf, size_t count)
{
	int ret;
	unsigned long val;
	// 将char ×转换成 unsigned long类型
	ret = kstrtoul(buf, 0, &val);
	if (ret < 0)
		return ret;
	tunables->io_is_busy = val;
	return count;
}
// 
static ssize_t show_boost(struct cpufreq_interactive_tunables *tunables, char *buf)
{
	return sprintf(buf, "%d\n", tunables->boost_val);
}