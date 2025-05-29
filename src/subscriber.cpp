// === subscriber.cpp ===
#include <iostream>
#include <ddscxx/dds/dds.hpp>
#include <ddscxx/dds/core/cond/WaitSet.hpp>
#include "StringMessage.hpp"

int main() {
    // Create a DomainParticipant on domain 0
    dds::domain::DomainParticipant dp(0);

    // Create a Topic with our generated type
    dds::topic::Topic<example::StringMessage> topic(dp, "StringTopic");

    // Create a Subscriber and DataReader
    dds::sub::Subscriber sub(dp);
    dds::sub::DataReader<example::StringMessage> dr(sub, topic);

    // Set up a ReadCondition and WaitSet
    dds::sub::cond::ReadCondition rc(
        dr,
        dds::sub::status::DataState::any(),
        [](const dds::sub::cond::ReadCondition&) {}
    );
    dds::core::cond::WaitSet ws;
    ws += rc;

    std::cout << "Subscriber listening..." << std::endl;
    while (true) {
        // Block until data arrives
        ws.wait(dds::core::Duration::from_secs(10));

        // Take samples
        auto samples = dr.take();
        for (auto& sample : samples) {
            if (sample.info().valid()) {
                std::cout << "Received: " << sample.data().content() << std::endl;
            }
        }
    }

    return 0;
}
