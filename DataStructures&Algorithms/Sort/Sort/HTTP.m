//
//  HTTP.m
//  Sort
//
//  Created by le on 2018/11/23.
//  Copyright © 2018 le. All rights reserved.
//

#import "HTTP.h"

@implementation HTTP

- (void)OSIModel {
    /*
     OSI七层模型
     1.物理层  bit
     2.数据链路层
     3.网络层   该层包含的协议:IP、ICMP、ARP、RARP等
     4.传输层   最重要的一层。定义了数据传输的协议和端口号。如TCP协议、UDP协议
     5.会话层
     6.表示层
     7.应用层
     */
}

- (void)tcpipProtocol {
    /*
     TCP/IP 协议分成四层：
     1.应用层
            决定了向用户提供应用服务时通信的活动。包含FTP（File Transfer Protocol）,DNS（Domain Name System）,HTTP协议等。
     2.传输层
            传输层对上层应用层，提供处于网络连接中的两台计算机之间的数据传输。在传输层有两个性质不同的协议:
            TCP(Transmissiong Control Protocol)传输控制协议和UDP(User Data Protocol)用户数据报协议
     3.网络层(网络互联层)
            网络层用来处理在网络上流动的数据包。
     4.数据链路层（数据链路层，网络接口层）
            处理w连接网络的硬件部分。包括控制操作系统、硬件的设备驱动、NIC以及光纤等物理可见部分。
     
    */
}

- (void)ipProtocol {
    /*
     IP(Internet Protocol)网际协议位于网络层。
     主要是用于将各种数据包传送给对方。包含IP地址和MAC地址。
     IP地址指明了节点被p分配到的地址。
     MAC地址是指网卡所属的固定地址。
     IP间通信依赖于MAC地址。需要经过多台计算机和网络设备中转才能连接到对方，在进行中转时候会利用下一站中转设备的MAC地址来搜索下一个中转目标，这个时候会采用ARPx协议(Address Resolution Protocol)。ARP是一种用以解析地址的协议m，根据通信方的IP地址就可以反查出对应的MAC地址。
     */
}

- (void)threeHandshaking {
    /*
     TCP协议位于传输层，提供可靠的字节流服务。
     字节流服务：是为了方便传输，将大快数据分割成以报文段（segment）为单位的数据包进行管理
     可靠的传输服务：能够把数据准确可靠地传给对方。
     
     三次握手策略： 握手过程中使用了TCP的标志 SYN(synchronize)和ACK(acknowledge)
        1.发送端首先发送一个带SYN标志的数据包给对方
        2.接收端收到后，回传一个带有SYN/ACK标志的数据包来表示传达确认信息
        3.发送端再回传一个带ACK标志的数据包，代表握手结束。
    如果在握手过程中某个阶段莫名中断，TCP协议会再次以相同的顺序发送相同的数据包。
     */
}

- (void)dnsProtocol {
    /*
     DNS和HTTP一样位于应用层的协议。提供域名到IP地址之间的解析服务。
     DNS协议通过域名地址查找IP或者逆向从IP地址反查域名的服务。
     */
}

- (void)aboutHTTP {
    /*
     HTTP不保存状态，即无状态协议。HTTP协议自身不对请求和响应之间的通信状态进行保存。协议对发送过的请求或响应不做持久化处理。
     方法：
     Get、Post、Put、Delete、Trace、Connect、
     
     持久连接
     早期HTTP协议每进行一次通信就要断开一次。
     HTTP/1.1 持久连接，只要任意一端没有明确提出断开连接，则保持TCP连接状态。持久连接好处在于减少了TCP连接的重复建立和断开所造成的额外开销，
     减轻了服务器端的负载。
     
     管线化 pipelining
     早期的HTTP请求在发送后需等待并等到响应才能发送下一个请求，管线化允许同时并行发送多个请求。
     
     Cookie管理状态
     Cookie通过在请求和响应报文中写入Cookie信息来控制客户端的状态。
     
     
     HTTP报文信息
     客户端的HTTP报文叫做请求报文，服务端的HTTP报文叫做响应报文。
     编码技术可以将数据进行压缩再进行传输，可以提高传输效率。常用的内容编码gzip(GNU zip)、compress(UNIX系统的标准压缩)、
     deflate(zlib)、identity(不进行编码)
     
     HTTP状态码
     2xx:被正常处理
     3xx:重定向，表明浏览器需要执行某些特殊的处理来正确处理请求，
     403:Forbidden 被服务器你禁止
     404:Not Found 服务器没有对应的资源
     5xx:表示服务器本身发生错误
     
     
     代理、网关、隧道
     HTTP/1.1 允许一台HTTP服务器托管多个域名。
     在相同IP地址下，由于虚拟主机可以寄存多个不同主机名和域名的Web网站m，因此在发送HTTP请求时，不许在Host首部内完整指定
     主机名和域名的URI。
     
     
     ....
     
     
     
     
    
     */
}

- (void)httpAndHttps {
    /*
     HTTP缺点
     1.通信使用明文（不加密）,内容可能会被窃听
     2.不验证通信方的身份，因此有可能遭受伪装
     3.无法证明报文的完整性，有可能已遭篡改
     
     
     1.TCP/IP是可能被窃听的网络
     TCP/IP协议族的工作机制m，通信内容在所有的通信线路上都可能被窃听。即使是加密的通信，也会被窥视到通信内容。通信经过加密
     会让人无法破解报文信息的含义m，但加密处理后的报文信息本身还是会被看到。
     
     如何防止窃听
     1.通信加密
     HTTP本身没有加密机制，但是可以通过和SSL（Secure Socket Layer完全套接层）或TLS（Transport Layer Security安全层传输协议）组合使用，
     加密HTTP的通信内容。
     2.内容加密
     将参与通信的内容本身加密。把HTTP报文中所含的内容进行加密处理。客户端需要对HTTP报文进行加密处理后再发送请求。任然会存在被篡改的风险。
     
     
     2.不验证通信方的身份可能遭遇伪装
     HTTP协议中请求和响应不会对通信方进行确认。存在服务器是否就是发送请求中URI真正指定的主机、返回的响应是否真的返回到实际请求的客户端等问题。
     无法确认请求发送至目标的Web服务器是否是真正的服务器。有可能是伪装的Web服务器
     无法确认响应返回到的客户端是否是真的客户端。有可能是伪装的客户端
     无法确认正在通信的双方是否具备访问权限
     无法判断请求来自哪里
     无法阻止海量请求的Dos攻击。Denial of Service（拒绝服务攻击）
     
     验证证书
     HTTP协议无法确认通信方，但是SSL可以，SSL不仅提供加密处理，而且还使用了一种被称为证书的手段，可用于确定双方。
     证书由信任的第三方机构颁发，用以证明服务器和客户端是实际存在的。
     
     
     3.无法验证报文完整性，可能已遭篡改
        HTTP协议无法证明通信的报文完整性，因此在相应过程中内容遭到篡改也无法获悉。
        请求或相应在传输途中，遭攻击者拦截并篡改内容的攻击被称为中间人攻击.Man-in-the-Middle attack(MITM)
     
     如何防止篡改
        MD5、SHA-1等算法都不能保证结果正确
     
     
     
     HTTPS
        HTTP + 加密 + 认证 + 完整性保护 = HTTPS
        在HTTP上再加入加密处理和认证等机制，就是HTTPS（HTTP Secure）.
        HTTPS是身披SSL外壳的HTTP
        HTTPS不是应用层的新协议，只是HTTP通信接口部分用SSL和TLS协议t代替。
        通常HTTP直接和TCP通信，当使用SSL时，就变成HTTP先和SSL通信，再有SSL和TCP通信。
     
     
        加密和解密用同一个秘钥的方式称为共享秘钥加密（对称秘钥加密）
        SSL
        SSL采用公开秘钥加密（Public-key cryptography）加密处理方式
        公开秘钥加密使用一对非对称的秘钥，一把叫做私有秘钥，一把叫做公开秘钥。
     
        HTTPS采用混合加密机制
     
        证明公开秘钥正确性的证书
     
     
     HTTPS通信过程
     1.客户端发送Client Hello 报文开始SSL通信，报文中包含客户端的SSL指定版本，加密组件列表（加密算法和秘钥长度）
     2.服务器可以进行SSL通信时，会以Server Hello报文作为应答。报文中也包含SSL版本、加密组件。服务器的加密组件是从接收到的客户端加密组件筛选出来的。
     3.服务器发送Certificate报文。报文中包含公开秘钥证书
     4.服务器发送Server Hello Done报文通知客户端，最初阶段的SSL握手协商结束
     5.SSL第一次握手结束后，客户端以Client Key Exchange报文作为回应。报文中包含通信中使用的随机密码串。
     6.客户端继续发送Change Cipher Spec报文。报文会提示服务器，在此报文之后的通信会采用Pre-master secret秘钥密码
     7.客户端发送Finished报文。报文包含连接至今全部报文的整体校验值。只有服务器正确解密该报文才能确定握手协商是否成功
     8.服务器同样发送Change Cipher Spec报文
     9.服务器同样发送Finished报文
     10.客户端与服务端的Finished报文交换完毕之后，SSL连接简历完成，此时开始进行应用层协议的通信，发送HTTP请求
     11.发送HTTP相应
     12.客户端断开连接，发送close_notify报文，在之后发送TCP FIN报文来关闭与TCP的通信。
     
     
     SSL和TLS
     Secure Socket Layer
     Transport Layer Security
     
     */
}

- (void)preventHttpHijacking {
    /*
     
     */
}


//标记指针
//标记指针在OC中末尾总是为1，如果指针默认不是1，说明不是真正的指针，因为没有内存对齐。
//64位指针可以容纳8个ASCII 字符。
//常量字符串从来不设置为标记指针

@end
