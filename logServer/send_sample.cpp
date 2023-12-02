#include <iostream>
#include <fstream>
#include <sstream>
#include "sample.pb.h"
#include <boost/asio.hpp>

int main() {
    // Create a Protobuf message
    ProtobufLog::Sample mysample;
    mysample.set_run(true);
    mysample.set_group("Demo");
    mysample.set_name("jack");
    mysample.set_age(26);

    // Serialize the Protobuf message to binary
    std::string serialized_message;
    if (!mysample.SerializeToString(&serialized_message)) {
        std::cerr << "Failed to serialize Protobuf message." << std::endl;
        return 1;
    }

    // Establish a TCP connection to Logstash
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::socket socket(io_context);
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 9601);

    try {
        socket.connect(endpoint);

        // Send the serialized Protobuf message to Logstash
        boost::asio::write(socket, boost::asio::buffer(serialized_message));

        // Close the socket
        socket.close();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

