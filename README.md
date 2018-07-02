# cethping

Raw socketで通信。[ethping](https://github.com/y-sira/pyng)を参考。パケットを作って文字列"Hi"を送信する。


Environment
-------

- Ubuntu14.04

Usage
-------
### Compile
```bash
make
```

### Server


```bash
sudo cethpingd $INTERFACE_NAME
```

### Client

```bash
sudo cethping $DESTINATION_MAC_ADDRESS $SOURCE_INTERFACE_NAME
```


Screen shot
-------
![screen shot](images/image1.png)


