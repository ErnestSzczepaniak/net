#ifdef build_platform_host

#define CATCH_CONFIG_MAIN
#include "build.h"
#include "test.h"

#else

#include "build.h"

// Thread * thread_emac = nullptr;

// void handler_irq()
// {
//     auto result = emac::receive();
//     thread::send(thread_emac, result);
//     emac::interrupt_ack();
// }

// unsigned char mem[4096][512];

// void process(unsigned char * buffer_request, int size)
// {
//     auto request_eth = net::eth::Header(buffer_request);

//     if (request_eth.type != net::eth::type::Aoe) return;

//     auto request_aoe = net::aoe::Header(buffer_request);

//     if (request_aoe.flag_response == true) return;

//     unsigned char buffer_response[2048];
//     memset(buffer_response, 0, 2048);

//     auto response_eth = net::eth::Header(buffer_response);

//     response_eth.destination = request_eth.source;
//     response_eth.source = net::eth::address::Empty;
//     response_eth.type = net::eth::type::Aoe;

//     auto response_aoe = net::aoe::Header(buffer_response);

//     response_aoe.version = 1;
//     response_aoe.flag_response = true;
//     response_aoe.flag_error = false;
//     response_aoe.error = 0;
//     response_aoe.address_major = 0x0001;
//     response_aoe.address_minor = 0x01;
//     response_aoe.command = (unsigned char) request_aoe.command;
//     response_aoe.tag = (unsigned int) request_aoe.tag;

//     if (request_aoe.command == net::aoe::command::Query_config_information)
//     {   
//         auto response_aoe_query = net::aoe::query::Header(buffer_response);

//         response_aoe_query.buffer_count = 0x1; // message queue
//         response_aoe_query.firmware_version = 0x0000;
//         response_aoe_query.sector_count = 2; // sectors per 1 transaction
//         response_aoe_query.aoe_version = 1;
//         response_aoe_query.command = net::aoe::query::command::Read_config_string;
//         response_aoe_query.config_string_length = 0;

//         emac::send(buffer_response, 32);
//     }
//     else if (request_aoe.command == net::aoe::command::Issue_ata_command)
//     {
//         auto request_aoe_issue = net::aoe::issue::Header(buffer_request);
//         auto response_aoe_issue = net::aoe::issue::Header(buffer_response);

//         response_aoe_issue.status_device_ready = true;
//         response_aoe_issue.lba = (unsigned int) request_aoe_issue.lba;

//         if (request_aoe_issue.command == net::aoe::issue::command::Identify_Device)
//         {
//             auto response_aoe_identify = net::aoe::issue::identify::Header(buffer_response);

//             response_aoe_identify.serial_number = net::aoe::issue::identify::String_serial_number("2.3:en2");
//             response_aoe_identify.logical_sector_number = 4096;

//             emac::send(buffer_response, 512 + 36);
//         }
//         else if (request_aoe_issue.command == net::aoe::issue::command::Read_sectors_with_retry)
//         {
//             unsigned int lba = request_aoe_issue.lba;
//             unsigned int count = request_aoe_issue.sector_count;

//             if (count == 1)
//             {
//                 memcpy(&buffer_response[36], &mem[lba][0], 512);
//                 emac::send(buffer_response, 512 + 36);
//             }
//             else
//             {
//                 memcpy(&buffer_response[36], &mem[lba][0], 512);
//                 memcpy(&buffer_response[36 + 512], &mem[lba + 1][0], 512);
//                 emac::send(buffer_response, 1024 + 36);
//             } 
//         }
//         else if (request_aoe_issue.command == net::aoe::issue::command::Write_sectors_with_retry)
//         {
//             unsigned int lba = request_aoe_issue.lba;
//             unsigned int count = request_aoe_issue.sector_count;

//             memcpy(&mem[lba][0], &buffer_request[36], 512);
//             if (count == 2) memcpy(&mem[lba + 1][0], &buffer_request[36 + 512], 512);

//             emac::send(buffer_response, 36);
//         }
//     }
// }

// void handler_emac()
// {
//     _o("Buffer @ 0x%08x", mem);
//     emac::init();

//     interrupt::enable(152, 0, handler_irq);

//     while(1)
//     {
//         auto [owner, request] = thread::receive<emac::Result>();
    
//         process((unsigned char *) request.data, request.size);

//         emac::receive_ack();
//     }
// }

int main()
{

    while(1);
}

#endif
