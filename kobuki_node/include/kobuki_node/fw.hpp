#ifndef KOBUKI_FW_DATA_HPP__
#define KOBUKI_FW_DATA_HPP__

#include <ecl/containers.hpp>
#include <packet_handler/payload_base.hpp>
#include <iclebo_comms/iCleboHeader.h>
#include <iclebo_comms/iCleboFW.h>

namespace kobuki {

class FWData : public packet_handler::payloadBase
{
public:
	// container
	iclebo_comms::iCleboFW data;
	
	// methods
	bool serialise( ecl::PushAndPop<unsigned char> & byteStream )
	{
		if(!(byteStream.size()>0)) { 
			ROS_WARN_STREAM("kobuki_node: iclebo_fw: serialise failed. empty byte stream."); 
			return false; 
		}

		buildBytes( data.header_id,		byteStream );
		buildBytes( data.fw_version,			byteStream );
		return true;
	}

	bool deserialise( ecl::PushAndPop<unsigned char> & byteStream )
	{
		if(!(byteStream.size()>0)) { 
			ROS_WARN_STREAM("kobuki_node: iclebo_fw: deserialise failed. empty byte stream."); 
			return false; 
		}

		buildVariable( data.header_id, 	byteStream );
		buildVariable( data.fw_version, 		byteStream );

		//showMe();
		return constrain();
	}

	bool constrain()
	{
		return true;
	}

	void showMe()
	{
		//printf("--[%02x || %03d | %03d | %03d]\n", data.bump, acc[2], acc[1], acc[0] );
	}
};

} // namespace kobuki

#endif /* KOBUKI_FW_DATA_HPP__ */

