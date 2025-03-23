#include <linux/regmap.h>

static const struct regmap_config my_regmap_config = {
    .name = "my_i2c_device",
    .reg_bits = 8,
    .val_bits = 8,
    .max_register = 0xFF,
};

static int my_probe(struct i2c_client *client) {
    struct regmap *regmap;
    int ret;
    unsigned int val;

    regmap = devm_regmap_init_i2c(client, &my_regmap_config);
    if (IS_ERR(regmap))
        return PTR_ERR(regmap);

    // 读取寄存器 0x00
    ret = regmap_read(regmap, 0x00, &val);
    if (ret < 0)
        return ret;

    // 向寄存器 0x01 写入 0xAA
    ret = regmap_write(regmap, 0x01, 0xAA);
    
    return ret;
}