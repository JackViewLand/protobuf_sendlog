# logstash install protobuf
FROM elastic/logstash:7.16.3
RUN logstash-plugin install logstash-codec-protobuf
CMD ["bin/logstash", "-f", "/usr/share/logstash/pipeline/logstash.conf"]
