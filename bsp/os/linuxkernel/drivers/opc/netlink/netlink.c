#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/sched.h>
#include <net/sock.h>
#include <net/netlink.h>

#define NETLINK_TEST 28
struct sock *nl_sk = NULL;
EXPORT_SYMBOL_GPL(nl_sk);

const char* kernel_send_str = "data form kernel wowo";

void nl_data_ready (struct sk_buff *__skb)
{
	struct sk_buff *skb;
	struct nlmsghdr *nlh;
	u32 pid;
	int rc;
	int len = NLMSG_SPACE(1200);
	char str[100];

	printk("netlink_kernel_create callback.\n");
	skb = skb_get(__skb);
	if (skb->len >= NLMSG_SPACE(0)) {
		nlh = nlmsg_hdr(skb);/*获取netlink数据包中netlink header的起始地址*/
		/*宏定义NLMSG_DATA(nlh)返回指向netlink消息体的payload的指针*/
		memcpy(str,NLMSG_DATA(nlh), sizeof(str));
		printk("[%s]recv data:[%s]\n", __func__, str);
		pid = nlh->nlmsg_pid; /*pid of sending process */
		printk("net_link: pid is %d\n", pid);
		kfree_skb(skb);

		skb = alloc_skb(len, GFP_ATOMIC);
		if (!skb){
			printk(KERN_ERR "net_link: allocate failed.\n");
			return;
		}

		nlh = nlmsg_put(skb,0,0,0,1200,0);
		NETLINK_CB(skb).portid = 0; /* from kernel */
		memcpy(NLMSG_DATA(nlh), kernel_send_str, strlen(kernel_send_str));
		rc = netlink_unicast(nl_sk, skb, pid, MSG_DONTWAIT);
		if (rc < 0) {
			printk(KERN_ERR "net_link: can not unicast skb (%d)\n", rc);
		}
	}
}

int init_module()
{
	struct netlink_kernel_cfg cfg = {
		.input		= nl_data_ready,
	};

	nl_sk = netlink_kernel_create(&init_net, NETLINK_TEST, &cfg);
	if (!nl_sk) {
		printk(KERN_ERR "net_link: Cannot create netlink socket.\n");
		return -EIO;
	}

	printk(" create socket ok.\n");
	return 0;
}

void cleanup_module( )
{
	if (nl_sk != NULL){
		sock_release(nl_sk->sk_socket);
	}

	printk("net_link: remove ok.\n");
}

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("fansaihua");