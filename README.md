# measurementor

OS Setting
受信バッファのサイズがデフォルト値の場合、ptsからデータを受信する際にバッファオーバフローを起こし、正常にデータが受信できません。
/etc/sysctl.confに以下を設定する必要があります。

net.ipv4.tcp_rmem = 4096 131072 6291456
net.ipv4.tcp_wmem = 4096 131072 6291456

また、設定を反映するには以下のコマンドを実行します。
# sysctl -p
