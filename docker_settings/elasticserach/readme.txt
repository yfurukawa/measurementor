elasticsearch起動時に発生するエラーへの対応
elasticsearchは多くのメモリを必要とする。このため、vm.max_map_countの値がデフォルトの65530だと少なすぎてエラーコード78で異常終了してしまう。
対応として、以下のコマンドでメモリマップの割当を増やしてやる。

sudo sysctl -w vm.max_map_count=262144


sudo docker network create elknet
cosign verify --key cosign.pub docker.elastic.co/elasticsearch/elasticsearch:8.12.1
sudo docker run --name es01 --network elknet -p 9200:9200 -p 9300:9300 -e "discovery.type=single-node" -e "network.host=0.0.0.0" -it -m 1GB elasticsearch:8.12.1
/usr/share/elasticsearch/bin/elasticsearch-reset-password -u elastic
/usr/share/elasticsearch/bin/elasticsearch-create-enrollment-token -s kibana
sudo docker cp es01:/usr/share/elasticsearch/config/certs/http_ca.crt .
curl --cacert http_ca.crt -u elastic:password https://localhost:9200


sudo docker run --name kb01 --network elknet -p 5601:5601 kibana:8.12.1


https://www.elastic.co/guide/en/elasticsearch/reference/8.12/docker.html#remove-containers-docker
