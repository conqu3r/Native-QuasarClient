#pragma once

#include <vector>
#include "tools/serializer.h"
#include "tools/deserializer.h"

#define MAX_PACKET_SIZE (1024 * 1024) * 5

namespace quasar {
		namespace packets {

				enum QuasarPacketId {
						PACKET_UNKNOWN = 0,
						PACKET_GET_AUTHENTICATION = 106,
						PACKET_GET_AUTHENTICATION_RESPONSE = 56,
						PACKET_GET_PROCESSES = 97,
						PACKET_DO_PROCESS_KILL = 96,
						PACKET_DO_PROCESS_START = 95,
						PACKET_GET_PROCESSES_RESPONSE = 49,
						PACKET_DO_SHOW_MESSAGEBOX = 85,
						PACKET_SET_STATUS = 55,
						PACKET_DO_SHUTDOWN_ACTION = 75
				};

				class quasar_packet {
				public:
						virtual ~quasar_packet() {
						}

						quasar_packet();
						quasar_packet(QuasarPacketId id);

						QuasarPacketId get_id() const;

						static bool is_unknown(const quasar_packet &packet) {
								return packet.get_id() == PACKET_UNKNOWN;
						}

						static bool is_unknown(const std::shared_ptr<quasar_packet> packet) {
								return packet == nullptr || packet->get_id() == PACKET_UNKNOWN;
						}

				protected:
						tools::serializer m_serializer;
						tools::deserializer m_deserializer;

						// must be called at start of serialize functions
						void begin_serialization();
						// must be called at the end of serialize functions
						void finalize_serialization();

				private:
						QuasarPacketId m_id;

						void write_header(std::vector<unsigned char> &payloadBuf) const;
				};
		}
}