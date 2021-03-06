# MCU Encryption

针对不具有 **ARM TrustZone** 功能或者 **Secure Boot** 功能的单片机设计的<br>
轻量级具有安全加密以及安全升级功能的 **Bootloader**
<br>

## 版本更新历史

版本|作者|时间|描述
----|----|----|----
0.0.1|Egahp|2021.10.01|创建项目

<br>

## 项目进程

- [x] 构建Debug框架
- [x] 构建USB HID通讯
- [x] 移植LVGL
- [ ] 唯一ID的实时运算读取
- [ ] 唯一ID检测触发模块
- [ ] CRC检验
- [ ] BootLoader功能
- [ ] 通过USB HID 的升级功能
- [x] 安全传输，TEA 加密
- [ ] 安全传输，AES 128 加密
- [ ] 安全传输，RSA 加密
- [ ] 部分MCU带有的永久锁死功能
