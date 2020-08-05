// Copyright 2019 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <uxr/agent/utils/CLI.hpp>
#include <uxr/agent/types/XRCETypes.hpp>
#include <uxr/agent/utils/Callbacks.hpp>
#include <csignal>

// void printGUID(const eprosima::fastrtps::rtps::GUID_t& guid) {
//     std::cout <<  "GUID:\n\t entityId.entityKind: " << (int) guid.entityId().entityKind() << "\n";
//     std::cout <<  "\t entityId.m_entityKey: ";

//     for (size_t i = 0; i < 3; i++){
//         std::cout << (int) guid.entityId().entityKey()[i] << " ";
//     }

//     std::cout <<  "\n\t guidPrefix: ";

//     for (size_t i = 0; i < 12; i++){
//         std::cout << (int) guid.guidPrefix()[i] << " ";
//     }
//     std::cout <<  "\n";
// }

// void on_create_callback(const dds::xrce::ObjectKind& kind, const eprosima::fastrtps::rtps::GUID_t& guid) {
//   std::cout <<  "ObjectKind: " <<(int) kind << "\n";
//   printGUID(guid);
// }

int main(int argc, char** argv)
{
    eprosima::uxr::UDPv4Agent agent_udp4(8888, eprosima::uxr::Middleware::Kind::FASTDDS);
    agent_udp4.set_verbose_level(6);

    // auto * cb_a = on_create_callback;
    // agent_udp4.add_oncreate_callback(cb_a);
    
    agent_udp4.start();

    while (true) { std::this_thread::sleep_for(std::chrono::seconds(1)); }

    return 0;
}
