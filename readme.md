# 列车调度模拟
## 食用方法
### mapgen.exe
首先使用mapgen随机生成一张列车与站点图表，它会自动覆盖创建一个名为`config`的文件，且格式如下
```ini
[STATIONS]
A:3.8
B:4.5
C:9.0
D:5.6
E:6.0
F:1.5
G:3.1
H:1.6
I:3.3
J:2.1
K:6.1
L:5.2
M:0.7
N:5.5
O:9.4
P:5.9
Q:7.2
R:9.9
S:8.4
T:7.1
U:2.9
V:6.7
W:3.4
X:2.8
Y:5.3
Z:3.5

[LINES]
K01:15:GWLJXDCUFYAKZEPBHO
K02:55:SNECPGUIAJORVKTHB
K03:2:TKGV
K04:51:EUMGFJX
K05:37:EVOYGA
K06:96:JAFVIBKWHORNTLDI
K07:11:CMEIGRVTQABXSFOUPNDHLJ
K08:83:AEYRL
K09:27:BWHN
K10:64:UQWEFTRGMXSKINO
K11:13:BLGFCUEOIC
K12:90:KFUHSJDMPYC
K13:43:FXTGDMIHLSUKAYNJO
K14:52:DKMTVCLIU
K15:33:DAOT
```
其中的`[STATIONS]`字段分别记录了每个站点名称与相应的`"cost"`，其意义为连接到该站点的花销。该值越小，在线路生成中越有可能被更多的线路选中；该值越大，越不容易出现在线路中。  
**注意**  
有些时候并不会生成完整的线路信息，如下列所示。如果出现该情况，请重新生成，该错误与每条线路随机生成的预期花销过低。
```
// 无效
K01:10:
K02:20:A

// 有效
K03:30:AB...
```
#### 参数详解[TODO]
```bash
./mapgen.exe <站点数> <线路数> [--markdown]
```
### scheme.exe
此程序依据生成的`config`文件，根据程序运行参数指定的人数给出调度策略
#### 参数详解
```bash
./scheme.exe <人数> [其他配置文件] [--debug]
```
- 人数
    - 此参数指定了本次模拟所要调度的人员总数，即随机查询次数
- 其他配置文件
    - 此参数不填的情况默认使用同目录下`config`文件
- debug[TODO]
    - 此参数开启调试模式
#### 输出样式
```
{002}<S -> U>
K02SNECPGUIAJORVKTHB[S -> U]
K07CMEIGRVTQABXSFOUPNDHLJ[S -> U]
K10UQWEFTRGMXSKINO[S -> U]
K12KFUHSJDMPYC[S -> U]
K13FXTGDMIHLSUKAYNJO[S -> U]

{编号}<出发地 -> 目的地>
车辆编号与总线路[出发地 -> 目的地]
车辆编号与总线路[出发地 -> 目的地]
...
车辆编号与总线路[出发地 -> 中转地] & 车辆编号与总线路[中转地 -> 目的地]
...
```

## 运行效率
```shell
$ time ./scheme.exe 1000

real    0m0.022s
user    0m0.004s
sys     0m0.019s

$ time ./scheme.exe 10000

real    0m0.054s
user    0m0.030s
sys     0m0.024s

$ time ./scheme.exe 100000

real    0m0.553s
user    0m0.240s
sys     0m0.138s
```

## TODO
- `mapgen`的参数化生成
- 可变站点与线路数量适应
- 余票扣除与空票提示