# Logstash 使用 Protobuf 傳送 Log

這是一個簡單的 lab，使用兩台 Logstash 進行 Protobuf 格式的 log 發送與接收，兩台 Logstash 中間有串接 Kafka 進行緩衝。

# 安裝步驟

本次 lab 使用 Docker 與 Docker Compose，請先行安裝 Docker 與 Docker Compose。

## 相關套件安裝
```bash
sudo apt-get update
```

安裝 kafkacat：
```bash
sudo apt-get install -y kafkacat
```

安裝 Protobuf 編譯器：
```bash
sudo apt-get install -y protobuf-compiler
```

安裝 C++ 編譯器：
```bash
sudo apt-get install -y gcc g++
```

安裝 C++ 相依套件：
```bash
sudo apt-get install libasio-dev
```

# 使用方法
操作方式：專案 clone 下來之後，會有 2 個資料夾，請分別起兩台 server 來運行 logServer 與 kafka，請更改 .env 中 KAFKA_IP 成運行 Kafka 服務的 public IP
```bash
git clone https://github.com/JackViewLand/protobuf_sendlog.git
```

```bash
vi logServer/.env
```
```bash
vi kafka/.env
```

運行 Docker Compose：
```bash
docker-compose up -d 
```

## 架構
運行 send_sample_logstash1.exe -> logstash1 -> kafka -> logstash2 -> 寫入 protobuf_test.log
<img width="513" alt="截圖 2023-12-02 下午3 48 33" src="https://github.com/JackViewLand/protobuf_sendlog/assets/122655131/8066b2c3-9b42-443d-a1ae-3422c98fa5b8">

## schema
在 logServer/etc 中有 Protobuf 的 schema，可以依照需求更改，並使用以下指令進行編譯。

生成 logstash 支援的 ruby schema：
```bash
protoc --ruby_out=. sample.proto
```

本次使用 C++ 建立 socket 來發送 log 給 logstash1
生成 C++ 使用的 schema：

```bash
protoc --cpp_out=. sample.proto
```

C++ 編譯發送 protobuf log 程式指令：
```bash
g++ send.cpp sample.pb.cc -o send.exe -lprotobuf -lpthread
```
參考
* [JSON is incredibly slow: Here’s What’s Faster!](https://medium.com/data-science-community-srm/json-is-incredibly-slow-heres-what-s-faster-ca35d5aaf9e8)
* [protobuf-example](https://github.com/vaishnav-mk/protobuf-example?source=post_page-----ca35d5aaf9e8--------------------------------)
* [lua 應用 protobuf 轉二進制](https://github.com/starwing/lua-protobuf)
* [logstash 應用 protobuf 解析](https://neojos.com/blog/2018/01-30-protobufs在logstash中的应用/)
* [.proto 檔案介紹](https://github.com/mengbin92/protobuf/blob/master/docs/学习指南(proto3).md)
* [GitHub：logstash-codec-protobuf](https://github.com/logstash-plugins/logstash-codec-protobuf)
