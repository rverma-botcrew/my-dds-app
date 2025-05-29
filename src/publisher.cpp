// === publisher.cpp ===
#include <iostream>
#include <chrono>
#include <thread>
#include <ddscxx/dds/dds.hpp>
#include "StringMessage.hpp"

int main() {
    // Create a DomainParticipant on domain 0
    dds::domain::DomainParticipant dp(0);

    // Create a Topic with our generated type
    dds::topic::Topic<example::StringMessage> topic(dp, "StringTopic");

    // Create a Publisher and DataWriter
    dds::pub::Publisher pub(dp);
    dds::pub::DataWriter<example::StringMessage> dw(pub, topic);

    // Create and send messages in a loop
    example::StringMessage msg;
    for (int i = 1; i <= 10; ++i) {
        msg.content(std::string("Hello DDS #") + std::to_string(i));
        std::cout << "Publishing: " << msg.content() << std::endl;
        dw.write(msg);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    std::cout << "Publisher done." << std::endl;
    return 0;
}