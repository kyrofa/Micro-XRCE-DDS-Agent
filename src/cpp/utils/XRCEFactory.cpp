// Copyright 2018 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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

#include <micrortps/agent/utils/XRCEFactory.hpp>
#include <micrortps/agent/types/SubMessageHeader.hpp>

namespace eprosima {
namespace micrortps {

size_t XRCEFactory::get_total_size()
{
    return serializer_.get_serialized_size();
}

void XRCEFactory::header(const dds::xrce::MessageHeader& header)
{
    serializer_.serialize(header);
}

void XRCEFactory::status(const dds::xrce::STATUS_Payload& payload)
{
    submessage_header(dds::xrce::STATUS, 0x01, static_cast<uint16_t>(payload.getCdrSerializedSize()));
    serializer_.serialize(payload);
}

void XRCEFactory::status_agent(const dds::xrce::STATUS_AGENT_Payload& payload)
{
    submessage_header(dds::xrce::STATUS_AGENT, 0x01, static_cast<uint16_t>(payload.getCdrSerializedSize()));
    serializer_.serialize(payload);
}

void XRCEFactory::acknack(const dds::xrce::ACKNACK_Payload& payload)
{
    submessage_header(dds::xrce::ACKNACK, 0x01, static_cast<uint16_t>(payload.getCdrSerializedSize()));
    serializer_.serialize(payload);
}

void XRCEFactory::heartbeat(const dds::xrce::HEARTBEAT_Payload& payload)
{
    submessage_header(dds::xrce::HEARTBEAT, 0x01, static_cast<uint16_t>(payload.getCdrSerializedSize()));
    serializer_.serialize(payload);
}

void XRCEFactory::data(const dds::xrce::DATA_Payload_Data& payload)
{
    reply(dds::xrce::DATA, payload, dds::xrce::FORMAT_DATA_FLAG);
}

void XRCEFactory::data(const dds::xrce::DATA_Payload_Sample& payload)
{
    reply(dds::xrce::DATA, payload, dds::xrce::FORMAT_SAMPLE_FLAG);
}

void XRCEFactory::data(const dds::xrce::DATA_Payload_DataSeq& payload)
{
    reply(dds::xrce::DATA, payload, dds::xrce::FORMAT_DATA_SEQ_FLAG);
}

void XRCEFactory::data(const dds::xrce::DATA_Payload_SampleSeq& payload)
{
    reply(dds::xrce::DATA, payload, dds::xrce::FORMAT_SAMPLE_SEQ_FLAG);
}

void XRCEFactory::data(const dds::xrce::DATA_Payload_PackedSamples& payload)
{
    reply(dds::xrce::DATA, payload, dds::xrce::FORMAT_PACKED_SAMPLES_FLAG);
}

void XRCEFactory::submessage_header(const dds::xrce::SubmessageId submessage_id,
                                    const uint8_t flags,
                                    const uint16_t submessage_length)
{
    dds::xrce::SubmessageHeader subMessage = dds::xrce::SubmessageHeader();
    subMessage.submessage_id(submessage_id);
    subMessage.flags(flags);
    subMessage.submessage_length(submessage_length);
    serializer_.serialize(subMessage); // Add submessage
}

void XRCEFactory::reply(const dds::xrce::SubmessageId submessage_id,
                        const dds::xrce::BaseObjectRequest& object_reply,
                        uint8_t data_flags)
{
    submessage_header(submessage_id, data_flags | 0x01, static_cast<uint16_t>(object_reply.getCdrSerializedSize()));
    serializer_.serialize(object_reply);
}

} // namespace micrortps
} // namespace eprosima