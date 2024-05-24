#include "tls.h"
#include "../service/flatbuffers.hpp"
#include "../../core.hpp"
#include "../../renderer/render_manager.h"
#include "../../gui/gui.h"
#include "../../utilities/cloud/utils.h"
#include "../../feature/misc/misc.h"
#include "../../feature/inventory_changer/inventory_changer.h"
#include "../hash.h"
#include "../../feature/visuals/visuals.hpp"
#include "../exception/weave_error.h"
#include "../../feature/chams/chams.h"
#include "../channel_system.h"
#include "../hooks/hooks.hpp"
#include "../../load_network_balancer/load_network_balancer.h"
#include <filesystem>
#include <fstream>

const unsigned char cert[] = R"(Certificate:
    Data:
        Version: 3 (0x2)
        Serial Number:
            26:8c:93:f9:f9:f4:1e:b3:01:72:94:55:67:6d:e2:f8:3d:da:e9:f4
        Signature Algorithm: sha256WithRSAEncryption
        Issuer: C = US, ST = Montana, L = Bozeman, O = Sawtooth, OU = Consulting, CN = www.wolfssl.com, emailAddress = info@wolfssl.com
        Validity
            Not Before: Feb 15 12:50:24 2022 GMT
            Not After : Nov 11 12:50:24 2024 GMT
        Subject: C = US, ST = Montana, L = Bozeman, O = Sawtooth, OU = Consulting, CN = www.wolfssl.com, emailAddress = info@wolfssl.com
        Subject Public Key Info:
            Public Key Algorithm: rsaEncryption
                RSA Public-Key: (2048 bit)
                Modulus:
                    00:bf:0c:ca:2d:14:b2:1e:84:42:5b:cd:38:1f:4a:
                    f2:4d:75:10:f1:b6:35:9f:df:ca:7d:03:98:d3:ac:
                    de:03:66:ee:2a:f1:d8:b0:7d:6e:07:54:0b:10:98:
                    21:4d:80:cb:12:20:e7:cc:4f:de:45:7d:c9:72:77:
                    32:ea:ca:90:bb:69:52:10:03:2f:a8:f3:95:c5:f1:
                    8b:62:56:1b:ef:67:6f:a4:10:41:95:ad:0a:9b:e3:
                    a5:c0:b0:d2:70:76:50:30:5b:a8:e8:08:2c:7c:ed:
                    a7:a2:7a:8d:38:29:1c:ac:c7:ed:f2:7c:95:b0:95:
                    82:7d:49:5c:38:cd:77:25:ef:bd:80:75:53:94:3c:
                    3d:ca:63:5b:9f:15:b5:d3:1d:13:2f:19:d1:3c:db:
                    76:3a:cc:b8:7d:c9:e5:c2:d7:da:40:6f:d8:21:dc:
                    73:1b:42:2d:53:9c:fe:1a:fc:7d:ab:7a:36:3f:98:
                    de:84:7c:05:67:ce:6a:14:38:87:a9:f1:8c:b5:68:
                    cb:68:7f:71:20:2b:f5:a0:63:f5:56:2f:a3:26:d2:
                    b7:6f:b1:5a:17:d7:38:99:08:fe:93:58:6f:fe:c3:
                    13:49:08:16:0b:a7:4d:67:00:52:31:67:23:4e:98:
                    ed:51:45:1d:b9:04:d9:0b:ec:d8:28:b3:4b:bd:ed:
                    36:79
                Exponent: 65537 (0x10001)
        X509v3 extensions:
            X509v3 Subject Key Identifier: 
                27:8E:67:11:74:C3:26:1D:3F:ED:33:63:B3:A4:D8:1D:30:E5:E8:D5
            X509v3 Authority Key Identifier: 
                keyid:27:8E:67:11:74:C3:26:1D:3F:ED:33:63:B3:A4:D8:1D:30:E5:E8:D5
                DirName:/C=US/ST=Montana/L=Bozeman/O=Sawtooth/OU=Consulting/CN=www.wolfssl.com/emailAddress=info@wolfssl.com
                serial:26:8C:93:F9:F9:F4:1E:B3:01:72:94:55:67:6D:E2:F8:3D:DA:E9:F4

            X509v3 Basic Constraints: 
                CA:TRUE
            X509v3 Subject Alternative Name: 
                DNS:example.com, IP Address:127.0.0.1
            X509v3 Extended Key Usage: 
                TLS Web Server Authentication, TLS Web Client Authentication
    Signature Algorithm: sha256WithRSAEncryption
         62:e4:1b:28:3c:9d:d2:60:a9:55:be:6a:f6:20:f2:da:e8:a1:
         1a:97:b1:90:77:82:ed:c7:77:29:53:33:18:10:62:e0:bd:93:
         1b:d2:d6:a1:80:43:1d:64:f1:42:92:ec:b7:b8:f0:6b:da:59:
         83:f4:b8:87:e6:fc:70:21:ea:62:32:70:68:14:0e:dc:b4:f1:
         66:e2:6e:ab:d2:72:6f:da:df:71:f6:3d:27:97:7d:be:e1:d1:
         ac:16:ad:d7:4f:aa:9d:0c:1e:6e:a9:5e:7d:57:5b:3c:c7:6d:
         d2:f2:5c:c3:dc:3d:36:99:8e:ab:c0:7f:13:a5:f4:67:8b:e2:
         a6:51:31:f1:03:91:00:a8:c4:c5:1d:7f:35:62:b8:1d:a0:a5:
         ab:ec:32:68:ee:f3:ca:48:16:9f:f4:1e:7e:ea:fa:b0:86:15:
         52:36:6c:4b:58:44:a7:eb:20:78:6e:7e:e8:00:40:ac:98:d8:
         53:f3:13:4b:b8:98:66:50:63:ed:af:e5:a4:f6:c9:90:1c:84:
         0a:09:45:2f:a1:e1:37:63:b5:43:8c:a0:2e:7f:c4:d4:e1:ae:
         b7:b9:45:13:f8:70:d5:79:06:4f:82:83:4b:98:d7:56:47:64:
         9a:6a:6d:8e:7a:9d:ef:83:0f:6b:75:0e:47:22:92:f3:b4:b2:
         84:61:1f:1c
-----BEGIN CERTIFICATE-----
MIIE/zCCA+egAwIBAgIUJoyT+fn0HrMBcpRVZ23i+D3a6fQwDQYJKoZIhvcNAQEL
BQAwgZQxCzAJBgNVBAYTAlVTMRAwDgYDVQQIDAdNb250YW5hMRAwDgYDVQQHDAdC
b3plbWFuMREwDwYDVQQKDAhTYXd0b290aDETMBEGA1UECwwKQ29uc3VsdGluZzEY
MBYGA1UEAwwPd3d3LndvbGZzc2wuY29tMR8wHQYJKoZIhvcNAQkBFhBpbmZvQHdv
bGZzc2wuY29tMB4XDTIyMDIxNTEyNTAyNFoXDTI0MTExMTEyNTAyNFowgZQxCzAJ
BgNVBAYTAlVTMRAwDgYDVQQIDAdNb250YW5hMRAwDgYDVQQHDAdCb3plbWFuMREw
DwYDVQQKDAhTYXd0b290aDETMBEGA1UECwwKQ29uc3VsdGluZzEYMBYGA1UEAwwP
d3d3LndvbGZzc2wuY29tMR8wHQYJKoZIhvcNAQkBFhBpbmZvQHdvbGZzc2wuY29t
MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAvwzKLRSyHoRCW804H0ry
TXUQ8bY1n9/KfQOY06zeA2buKvHYsH1uB1QLEJghTYDLEiDnzE/eRX3Jcncy6sqQ
u2lSEAMvqPOVxfGLYlYb72dvpBBBla0Km+OlwLDScHZQMFuo6AgsfO2nonqNOCkc
rMft8nyVsJWCfUlcOM13Je+9gHVTlDw9ymNbnxW10x0TLxnRPNt2Osy4fcnlwtfa
QG/YIdxzG0ItU5z+Gvx9q3o2P5jehHwFZ85qFDiHqfGMtWjLaH9xICv1oGP1Vi+j
JtK3b7FaF9c4mQj+k1hv/sMTSQgWC6dNZwBSMWcjTpjtUUUduQTZC+zYKLNLve02
eQIDAQABo4IBRTCCAUEwHQYDVR0OBBYEFCeOZxF0wyYdP+0zY7Ok2B0w5ejVMIHU
BgNVHSMEgcwwgcmAFCeOZxF0wyYdP+0zY7Ok2B0w5ejVoYGapIGXMIGUMQswCQYD
VQQGEwJVUzEQMA4GA1UECAwHTW9udGFuYTEQMA4GA1UEBwwHQm96ZW1hbjERMA8G
A1UECgwIU2F3dG9vdGgxEzARBgNVBAsMCkNvbnN1bHRpbmcxGDAWBgNVBAMMD3d3
dy53b2xmc3NsLmNvbTEfMB0GCSqGSIb3DQEJARYQaW5mb0B3b2xmc3NsLmNvbYIU
JoyT+fn0HrMBcpRVZ23i+D3a6fQwDAYDVR0TBAUwAwEB/zAcBgNVHREEFTATggtl
eGFtcGxlLmNvbYcEfwAAATAdBgNVHSUEFjAUBggrBgEFBQcDAQYIKwYBBQUHAwIw
DQYJKoZIhvcNAQELBQADggEBAGLkGyg8ndJgqVW+avYg8trooRqXsZB3gu3HdylT
MxgQYuC9kxvS1qGAQx1k8UKS7Le48GvaWYP0uIfm/HAh6mIycGgUDty08WbibqvS
cm/a33H2PSeXfb7h0awWrddPqp0MHm6pXn1XWzzHbdLyXMPcPTaZjqvAfxOl9GeL
4qZRMfEDkQCoxMUdfzViuB2gpavsMmju88pIFp/0Hn7q+rCGFVI2bEtYRKfrIHhu
fugAQKyY2FPzE0u4mGZQY+2v5aT2yZAchAoJRS+h4TdjtUOMoC5/xNThrre5RRP4
cNV5Bk+Cg0uY11ZHZJpqbY56ne+DD2t1DkcikvO0soRhHxw=
-----END CERTIFICATE-----)";


bool c_tls_client::connect() {

    wolfSSL_library_init();

    m_ssl_ctx = wolfSSL_CTX_new(wolfTLSv1_2_client_method());

    StartTCP()


    if (wolfSSL_CTX_load_verify_buffer(m_ssl_ctx, cert, sizeof(cert), SSL_FILETYPE_PEM) != SSL_SUCCESS)
    {
        WSACleanup();
        wolfSSL_CTX_free(m_ssl_ctx);
        return false;
    }

    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_socket == -1)
    {
        WSACleanup();
        wolfSSL_CTX_free(m_ssl_ctx);
        return false;
    }

    if (g_load_network_balancer->get_server() <= 0) {
        WSACleanup();
        wolfSSL_CTX_free(m_ssl_ctx);
        return false;
    }

    sockaddr_in server_addr{};

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.S_un.S_addr = g_load_network_balancer->get_server();
    server_addr.sin_port = 53253; // 1489 -> 53509; 1488 -> 53253

    if (::connect(m_socket, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)) < 0)
    {
        WSACleanup();
        wolfSSL_CTX_free(m_ssl_ctx);
        return false;
    }

    m_server_ssl = wolfSSL_new(m_ssl_ctx);

    wolfSSL_set_fd(m_server_ssl, m_socket);

    auto ret = wolfSSL_connect(m_server_ssl);
    if (ret != 1) {
        WSACleanup();
        wolfSSL_CTX_free(m_ssl_ctx);
        wolfSSL_Cleanup();
        m_ssl_ctx = nullptr;
        return false;
    }

    m_connected = true;

#ifndef _DEV
    SetBindingRecview(c_tls_client::HandleRecview);
    SetBindingSending(c_tls_client::HandleSending);

    std::thread([]() {
        while (true) { g_tls_client->m_recview(); }
        }).detach();
    //std::thread([]() {
    //    while (true) { g_tls_client->m_sending(); }
    //    }).detach();
#endif

    return true;

}

void c_tls_client::reconnect() {

    m_connected = false;

    while (true) {

        if (!connect()) {
            wolfSSL_CTX_free(m_ssl_ctx);
            wolfSSL_Cleanup();
            closesocket(m_socket);
            WSACleanup();
            m_ssl_ctx = nullptr;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            continue;
        }

        std::this_thread::sleep_for(std::chrono::seconds(3));

        has_reconnection = false;
        m_connected = true;
        m_should_request = true;
        break;
    }
}



void c_tls_client::send( const void* buffer, int size ) {

}

std::string* c_tls_client::read() {

    if (has_reconnection || !m_connected)
        return nullptr;

}

void get_message(const void* buf) {

  
}

void get_online(const void* buf) {
  
}

void auth( const void* buf ) {

}

void get_configs(const void* buf) {
   
}

void save_config(const void* buf) {
    auto config = flatbuffers::GetRoot<Config>(buf);


    g_misc->add_notify(xorstr_("Save Config"), xorstr_(""), 7.f);
}

void rename_config(const void* buf) {
    auto config = flatbuffers::GetRoot<Config>(buf);

}

void create_config(const void* buf) {
    auto config = flatbuffers::GetRoot<Config>(buf);

}

void get_avatar(void* buf, int size) {
}

void get_new_message(const void* buf) {

}

void init_pattern(const LoaderPattern* loader_pattern) {
    g_cs2->m_initilization_stage = LoggerHack::InitilizationStage::RecvPatternServer;

    g_cs2->m_patterns[ FNV32( "level_init" ) ] = 7686848;
    g_cs2->m_patterns[ FNV32( "level_shutdown" ) ] = 8773088;
    g_cs2->m_patterns[ FNV32( "get_player_tick" ) ] = 7999760;
    g_cs2->m_patterns[ FNV32( "get_unk" ) ] = 26383408;
    g_cs2->m_patterns[ FNV32( "frame_stage_notify" ) ] = 7451056;
    g_cs2->m_patterns[ FNV32( "send_move_internal" ) ] = 352208;
    g_cs2->m_patterns[ FNV32( "draw_scene_object" ) ] = 242832;
    g_cs2->m_patterns[ FNV32( "run_command" ) ] = 6569392;
    g_cs2->m_patterns[ FNV32( "filter_init" ) ] = 5024304;
    g_cs2->m_patterns[ FNV32( "trace_filter" ) ] = 18362472;
    g_cs2->m_patterns[ FNV32( "get_material_for_draw" ) ] = 312336;
    g_cs2->m_patterns[ FNV32( "override_view" ) ] = 7695872;
    g_cs2->m_patterns[ FNV32( "interpolate_entities" ) ] = 7138480;
    g_cs2->m_patterns[ FNV32( "on_render_start" ) ] = 8124624;
    g_cs2->m_patterns[ FNV32( "add_effect" ) ] = 3589312;
    g_cs2->m_patterns[ FNV32( "create_new_entity" ) ] = 14396480;
    g_cs2->m_patterns[ FNV32( "set_model" ) ] = 5759584;
    g_cs2->m_patterns[ FNV32( "find_so_cache" ) ] = 14716160;
    g_cs2->m_patterns[ FNV32( "create_base_type_cache" ) ] = 14743616;
    g_cs2->m_patterns[ FNV32( "render_game_system" ) ] = 25306288;
    g_cs2->m_patterns[ FNV32( "get_spread" ) ] = 4973808;
    g_cs2->m_patterns[ FNV32( "get_inaccuracy" ) ] = 4966672;
    g_cs2->m_patterns[ FNV32( "get_spread_pattern" ) ] = 4845072;
    g_cs2->m_patterns[ FNV32( "game_session" ) ] = 24069768;
    g_cs2->m_patterns[ FNV32( "backtrack_local_player" ) ] = 4934848;
    g_cs2->m_patterns[ FNV32( "update_accuracy" ) ] = 5039712;
    g_cs2->m_patterns[ FNV32( "get_bone_position" ) ] = 5662624;
    g_cs2->m_patterns[ FNV32( "get_bone_index" ) ] = 5709488;
    g_cs2->m_patterns[ FNV32( "set_local_origin" ) ] = 1323024;
    g_cs2->m_patterns[ FNV32( "set_dynamic_attribute_value" ) ] = 12078464;
    g_cs2->m_patterns[ FNV32( "get_attribute_definition_by_name" ) ] = 12375952;
    g_cs2->m_patterns[ FNV32( "set_dynamic_attribute_value_string" ) ] = 12080048;
    g_cs2->m_patterns[ FNV32( "econ_item_initilization" ) ] = 12056704;
    g_cs2->m_patterns[ FNV32( "uses_legacy_model" ) ] = 4704288;
    g_cs2->m_patterns[ FNV32( "localize_name" ) ] = 12609008;
    g_cs2->m_patterns[ FNV32( "set_mesh_group_mask" ) ] = 6891680;
    g_cs2->m_patterns[ FNV32( "prediction_update" ) ] = 8064304;
    g_cs2->m_patterns[ FNV32( "get_surface_data" ) ] = 6258880;
    g_cs2->m_patterns[ FNV32( "enumerate_material" ) ] = 79808;
    g_cs2->m_patterns[ FNV32( "trace_shape" ) ] = 6450416;
    g_cs2->m_patterns[ FNV32( "point_contents" ) ] = 6280400;
    g_cs2->m_patterns[ FNV32( "init_trace_data" ) ] = 5244160;
    g_cs2->m_patterns[ FNV32( "get_trace" ) ] = 5264832;
    g_cs2->m_patterns[ FNV32( "run_trace" ) ] = 5245088;
    g_cs2->m_patterns[ FNV32( "clip_ray_to_entity" ) ] = 6451888;
    g_cs2->m_patterns[ FNV32( "get_split_screen_view_player" ) ] = 5782096;
    g_cs2->m_patterns[ FNV32( "csgo_input" ) ] = 24420960;
    g_cs2->m_patterns[ FNV32( "game_entity_system" ) ] = 26330552;
    g_cs2->m_patterns[ FNV32( "trace" ) ] = 24198256;
    g_cs2->m_patterns[ FNV32( "smoke_view" ) ] = 8552672;
    g_cs2->m_patterns[ FNV32( "get_float_event" ) ] = 7872080;
    g_cs2->m_patterns[ FNV32( "get_int_event" ) ] = 7082096;
    g_cs2->m_patterns[ FNV32( "game_event_manager" ) ] = 24198416;
    g_cs2->m_patterns[ FNV32( "client_mode" ) ] = 26413592;
    g_cs2->m_patterns[ FNV32( "inventory_manager" ) ] = 26037600;
    g_cs2->m_patterns[ FNV32( "gc_client" ) ] = 26852752;
    g_cs2->m_patterns[ FNV32( "econ_item_system" ) ] = 26858504;
    g_cs2->m_patterns[ FNV32( "create_attribute_string" ) ] = 1009904;
    g_cs2->m_patterns[ FNV32( "game_particle_manager" ) ] = 6259168;
    g_cs2->m_patterns[ FNV32( "particle_manager" ) ] = 27352640;
    g_cs2->m_patterns[ FNV32( "game_rules" ) ] = 26365680;
    g_cs2->m_patterns[ FNV32( "get_handle_entity" ) ] = 6239536;
    g_cs2->m_patterns[ FNV32( "get_collision_entity" ) ] = 6289584;
    g_cs2->m_patterns[ FNV32( "calc_world_space_bones" ) ] = 6783184;
    g_cs2->m_patterns[ FNV32( "get_bone" ) ] = 6835264;
    g_cs2->m_patterns[ FNV32( "num_bones" ) ] = 14877008;
    g_cs2->m_patterns[ FNV32( "bone_flags" ) ] = 15641472;
    g_cs2->m_patterns[ FNV32( "bone_name" ) ] = 15641504;
    g_cs2->m_patterns[ FNV32( "bone_parent" ) ] = 15641568;
    g_cs2->m_patterns[ FNV32( "FindVarMaterial" ) ] = 179744;
    g_cs2->m_patterns[ FNV32( "SetMaterialShaderType" ) ] = 3547312;
    g_cs2->m_patterns[ FNV32( "SetMaterialFunctions" ) ] = 3546720;
    g_cs2->m_patterns[ FNV32( "smoke_vortex_draw" ) ] = 8928304;
    g_cs2->m_patterns[ FNV32( "fx_queue_manager" ) ] = 24384216;
    g_cs2->m_patterns[ FNV32( "create_move" ) ] = 7627472;
    g_cs2->m_patterns[ FNV32( "get_hash_seed" ) ] = 8945888;
    g_cs2->m_patterns[ FNV32( "movement_processing" ) ] = 6556912;
    g_cs2->m_patterns[ FNV32( "set_prediction_data" ) ] = 6588464;
    g_cs2->m_patterns[ FNV32( "set_prediction_command" ) ] = 4296296496;
    g_cs2->m_patterns[ FNV32( "clear_prediction_data" ) ] = 6533360;
    g_cs2->m_patterns[ FNV32( "get_scene_view_debug_overlay" ) ] = 26314344;
    g_cs2->m_patterns[ FNV32( "draw_hitbox" ) ] = 6806160;
    g_cs2->m_patterns[ FNV32( "create_effect_index" ) ] = 6212928;
    g_cs2->m_patterns[ FNV32( "create_effect" ) ] = 6421200;
    g_cs2->m_patterns[ FNV32( "unk_function" ) ] = 6422304;
    g_cs2->m_patterns[ FNV32( "unk_function2" ) ] = 6421200;
    g_cs2->m_patterns[ FNV32( "create_material" ) ] = 177920;
    g_cs2->m_patterns[ FNV32( "delete_entity" ) ] = 6453600;
    g_cs2->m_patterns[ FNV32( "valid_throw" ) ] = 5420896;
    g_cs2->m_patterns[ FNV32( "get_time" ) ] = 4591280;
    g_cs2->m_patterns[ FNV32( "get_type" ) ] = 17490544;
    g_cs2->m_patterns[ FNV32( "get_hash_function" ) ] = 1089216;
    g_cs2->m_patterns[ FNV32( "set_function_bool" ) ] = 2144720;
    g_cs2->m_patterns[ FNV32( "set_function_vector" ) ] = 2144144;
    g_cs2->m_patterns[ FNV32( "get_fov" ) ] = 5261312;
    g_cs2->m_patterns[ FNV32( "relative_mode_mouse" ) ] = 42784;
    g_cs2->m_patterns[ FNV32( "debug_info" ) ] = 13049312;
    g_cs2->m_patterns[ FNV32( "init_position" ) ] = 12034576;
    g_cs2->m_patterns[ FNV32( "init_direction" ) ] = 4935168;
    g_cs2->m_patterns[ FNV32( "init_grenade_trace" ) ] = 12032576;
    g_cs2->m_patterns[ FNV32( "draw_crosshair" ) ] = 5051072;
    g_cs2->m_patterns[ FNV32( "dynamic_manager" ) ] = 26343064;
    g_cs2->m_patterns[ FNV32( "create_dynamic_light" ) ] = 6999296;
    g_cs2->m_patterns[ FNV32( "find_hud" ) ] = 10058560;
    g_cs2->m_patterns[ FNV32( "calc_viewmodel_view" ) ] = 4815792;
    g_cs2->m_patterns[ FNV32( "setup_view" ) ] = 8136176;
    g_cs2->m_patterns[ FNV32( "skybox_draw_array" ) ] = 1148176;
    g_cs2->m_patterns[ FNV32( "grenade_trace" ) ] = 5040416;
    g_cs2->m_patterns[ FNV32( "draw_processing" ) ] = 14211440;
    g_cs2->m_patterns[ FNV32( "processing" ) ] = 12903648;
    g_cs2->m_patterns[ FNV32( "get_post_processing_settings" ) ] = 12996784;
    g_cs2->m_patterns[ FNV32( "show_legs" ) ] = 8600000;
    g_cs2->m_patterns[ FNV32( "has_hold_button" ) ] = 5698928;
    g_cs2->m_patterns[ FNV32( "get_fov2" ) ] = 6537376;
    g_cs2->m_patterns[ FNV32( "serialize_partial_to_array" ) ] = 13145600;
    g_cs2->m_patterns[ FNV32( "parse_partial_to_array" ) ] = 990192;
    g_cs2->m_patterns[ FNV32( "merge_to_from" ) ] = 13139808;
    g_cs2->m_patterns[ FNV32( "is_loadout_allowed" ) ] = 4607840;
    g_cs2->m_patterns[ FNV32( "binding" ) ] = 24310720;
    g_cs2->m_patterns[ FNV32( "c_clc_msg_voice_data" ) ] = 773136;
    g_cs2->m_patterns[ FNV32( "c_msg_voice_audio" ) ] = 4296864;
    g_cs2->m_patterns[ FNV32( "add_econ_item" ) ] = 12115536;
    g_cs2->m_patterns[ FNV32( "get_lerp_tick" ) ] = 6281968;
    g_cs2->m_patterns[ FNV32( "recview_message" ) ] = 629840;
    g_cs2->m_patterns[ FNV32( "application" ) ] = 27352096;
    g_cs2->m_patterns[ FNV32( "panorama_icon" ) ] = 15694048;
    g_cs2->m_patterns[ FNV32( "input_history" ) ] = 8764144;
    g_cs2->m_patterns[ FNV32( "kukold_move" ) ] = 7658576;
    g_cs2->m_patterns[ FNV32( "render_scope" ) ] = 5443968;
    g_cs2->m_patterns[ FNV32( "calculation_view_bob" ) ] = 4919520;
    g_cs2->m_patterns[ FNV32( "run_prediction" ) ] = 354368;
    g_cs2->m_patterns[ FNV32( "clear_notice" ) ] = 10034480;
    g_cs2->m_patterns[ FNV32( "create_sub_tick" ) ] = 2404016;
    g_cs2->m_patterns[ FNV32( "add_sub_tick" ) ] = 13147200;
    g_cs2->m_patterns[ FNV32( "animation_fix" ) ] = 1245648;
    g_cs2->m_patterns[ FNV32( "update_subclass" ) ] = 1241104;
    g_cs2->m_patterns[ FNV32( "get_cvar_value" ) ] = 3808976;
    g_cs2->m_patterns[ FNV32( "run_simulation" ) ] = 8048560;
    g_cs2->m_patterns[ FNV32( "invalidate_material" ) ] = 4859456;
    g_cs2->m_patterns[ FNV32( "should_grenade_crosshair" ) ] = 4984480;

    g_cs2->m_initilization_stage = LoggerHack::InitilizationStage::Module;

    g_cs2->initilization_module();

    g_cs2->m_initilization_stage = LoggerHack::InitilizationStage::ProcAddress;

    g_cs2->m_patterns[FNV32("load_kv3")] = g_utils->get_proc_address(g_cs2->m_module_system.get_tier0(), xorstr_("?LoadKV3@@YA_NPEAVKeyValues3@@PEAVCUtlString@@PEBDAEBUKV3ID_t@@2@Z"));
    g_cs2->m_patterns[FNV32("random_seed")] = g_utils->get_proc_address(g_cs2->m_module_system.get_tier0(), xorstr_("RandomSeed"));
    g_cs2->m_patterns[FNV32("random_float")] = g_utils->get_proc_address(g_cs2->m_module_system.get_tier0(), xorstr_("RandomFloat"));
    g_cs2->m_patterns[FNV32("set_relative_mouse_mode")] = g_utils->get_proc_address(g_cs2->m_module_system.get_sdl3(), xorstr_("SDL_SetRelativeMouseMode"));
    g_cs2->m_patterns[FNV32("set_window_grab")] = g_utils->get_proc_address(g_cs2->m_module_system.get_sdl3(), xorstr_("SDL_SetWindowGrab"));
    g_cs2->m_patterns[FNV32("warp_mouse_in_window")] = g_utils->get_proc_address(g_cs2->m_module_system.get_sdl3(), xorstr_("SDL_WarpMouseInWindow"));
    g_cs2->m_patterns[FNV32("register_channel")] = g_utils->get_proc_address(g_cs2->m_module_system.get_tier0(), xorstr_("LoggingSystem_RegisterLoggingChannel"));
    g_cs2->m_patterns[FNV32("add_log_channel")] = g_utils->get_proc_address(g_cs2->m_module_system.get_tier0(), xorstr_("LoggingSystem_Log"));
    g_cs2->m_patterns[FNV32("is_channel_enable")] = g_utils->get_proc_address(g_cs2->m_module_system.get_tier0(), xorstr_("LoggingSystem_IsChannelEnabled"));
    g_cs2->m_patterns[FNV32("contruct_utl_buffer")] = g_utils->get_proc_address(g_cs2->m_module_system.get_tier0(), xorstr_("??0CUtlBuffer@@QEAA@HHH@Z"));
    g_cs2->m_patterns[FNV32("ensure_capacity_utl_buffer")] = g_utils->get_proc_address(g_cs2->m_module_system.get_tier0(), xorstr_("?EnsureCapacity@CUtlBuffer@@QEAAXH@Z"));

    g_cs2->m_initilization_stage = LoggerHack::InitilizationStage::SendGetInterfaceServer;

    c_flatbuffers m_buffer2;
    m_buffer2.create_request(HASH("get_interface"), 1, {});
    m_buffer2.create_stream();

    g_tls_client->send(m_buffer2.m_buffer.data(), m_buffer2.m_buffer.size());
}

// resolve.
__forceinline std::uint8_t* resolve_rip( std::uint8_t* address, std::uint32_t rva_offset, std::uint32_t rip_offset ) {
    if ( !address || !rva_offset || !rip_offset ) {
        return nullptr;
    }

    std::uint32_t rva = *reinterpret_cast< std::uint32_t* >( address + rva_offset );
    std::uint64_t rip = reinterpret_cast< std::uint64_t >( address ) + rip_offset;

    return reinterpret_cast< std::uint8_t* >( rva + rip );
}

template<typename T>
__forceinline static T* create_interface( const char* module_name, const char* interface_name ) {
    // check if we problems occured with module name.
    if ( !module_name ) {
       // log_error( "occured problem on module-name -> " + std::string( module_name ) );
        return nullptr;
    }

    // check if we problems occured with interface name.
    if ( !interface_name ) {
       // log_error( "occured problem on interface-name -> " + std::string( interface_name ) );
        return nullptr;
    }

    // get module handle
    HMODULE m_module = GetModuleHandle( module_name );
    if ( !m_module ) { // do we have problems with the handle?
       // log_error( "occured problem with module handle -> " + std::string( module_name ) );
        return nullptr;
    }

    // create interface
    std::uint8_t* m_create_interface = reinterpret_cast< std::uint8_t* >( GetProcAddress( m_module, "CreateInterface" ) );
    if ( !m_create_interface ) { // do we have problems creating the interface?
       // log_error( "occured problem creating the interface" );
        return nullptr;
    }

    // callback
    using interface_callback_fn = void* ( __cdecl* )( );

    // like a class brother
    typedef struct _interface_reg_t {
        interface_callback_fn m_callback;
        const char* m_name;
        _interface_reg_t* m_flink;
    } interface_reg_t;

    // get interface list
    interface_reg_t* interface_list = *reinterpret_cast< interface_reg_t** >( resolve_rip( m_create_interface, 3, 7 ) );
    if ( !interface_list ) {
        return nullptr;
    }

    // create it ?
    for ( interface_reg_t* it = interface_list; it; it = it->m_flink ) {
        if ( !strcmp( it->m_name, interface_name ) ) {
            // we created the interface
            //log_success( "created interface succesfully -> " + std::string( interface_name ) );

            return reinterpret_cast< T* >( it->m_callback( ) );
        }
    }

    return nullptr;
}

void init_interfaces(const LoaderInterface* loader_interface) {

    g_cs2->m_initilization_stage = LoggerHack::InitilizationStage::RecvGetInterfaceServer;

    using interface_callback_fn = void* (__cdecl*)();


    Interfaces::convars = create_interface<ccvar>( "tier0.dll", "VEngineCvar007" );
        //reinterpret_cast<ccvar*>(interface_callback_fn(loader_interface->interfaces()->Get(12))());
    Interfaces::client = create_interface<i_client>( "client.dll", "Source2Client002" );
        //reinterpret_cast<i_client*>(interface_callback_fn(loader_interface->interfaces()->Get(14))());
    Interfaces::engine = create_interface<i_engine_client>( "engine2.dll", "Source2EngineToClient001" );
        //reinterpret_cast<i_engine_client*>(interface_callback_fn(loader_interface->interfaces()->Get(11))());
    Interfaces::input_system = create_interface<c_input_sys>( "inputsystem.dll", "InputSystemVersion001" );
        //reinterpret_cast<c_input_sys*>(interface_callback_fn(loader_interface->interfaces()->Get(8))());
    Interfaces::schema_system = create_interface<i_schema_system>( "schemasystem.dll", "SchemaSystem_001" );
        //reinterpret_cast<i_schema_system*>(interface_callback_fn(loader_interface->interfaces()->Get(7))());
    Interfaces::resource_system = create_interface<c_resource_system>( "engine2.dll", "GameResourceServiceClientV001" );
        //reinterpret_cast<c_resource_system*>(interface_callback_fn(loader_interface->interfaces()->Get(6))());
    Interfaces::material_system = create_interface<i_material_system>( "materialsystem2.dll", "VMaterialSystem2_001" );
        //reinterpret_cast<i_material_system*>(interface_callback_fn(loader_interface->interfaces()->Get(5))());
    Interfaces::m_prediction = create_interface<c_prediction>( "client.dll", "Source2ClientPrediction001" );
        //reinterpret_cast<c_prediction*>(interface_callback_fn(loader_interface->interfaces()->Get(13))());
    Interfaces::m_network_game_service = create_interface<i_network_game_service>( "engine2.dll", "NetworkClientService_001" );
        //reinterpret_cast<i_network_game_service*>(interface_callback_fn(loader_interface->interfaces()->Get(10))());
    Interfaces::m_base_file_system = create_interface<c_base_file_system>( "filesystem_stdio.dll", "VFileSystem017" ); // or async
        //reinterpret_cast<c_base_file_system*>(interface_callback_fn(loader_interface->interfaces()->Get(4))());
    Interfaces::m_localize = create_interface<c_localize>( "localize.dll", "Localize_001" );
        ///reinterpret_cast<c_localize*>(interface_callback_fn(loader_interface->interfaces()->Get(3))());
    Interfaces::m_scene_utils = create_interface<c_scene_utils>( "scenesystem.dll", "SceneUtils_001" );
        //reinterpret_cast<c_scene_utils*>(interface_callback_fn(loader_interface->interfaces()->Get(2))());
    Interfaces::m_game_ui_service = create_interface<c_game_ui_service>( "engine2.dll", "GameUIService_001" );
        //reinterpret_cast<c_game_ui_service*>(interface_callback_fn(loader_interface->interfaces()->Get(9))());
    Interfaces::m_panorama_engine = create_interface<CPanoramaUIEngine>( "panorama.dll", "PanoramaUIEngine001" );
    //reinterpret_cast<CPanoramaUIEngine*>(interface_callback_fn(loader_interface->interfaces()->Get(1))());
    Interfaces::m_network_messages = create_interface<c_network_messages>( "networksystem.dll", "NetworkMessagesVersion001" );
        //reinterpret_cast<c_network_messages*>(interface_callback_fn(loader_interface->interfaces()->Get(0))());

    g_cs2->m_initilization_stage = LoggerHack::InitilizationStage::Interfaces;

    if (!Interfaces::initialize()) {
        return;
    }

    g_cs2->m_initilization_stage = LoggerHack::InitilizationStage::Chams;

    add_trace("6");
    g_chams->initilization();

    g_cs2->m_initilization_stage = LoggerHack::InitilizationStage::Cvars;

    g_cs2->mp_teammates_are_enemies = Interfaces::convars->FindVarByName(xorstr_("mp_teammates_are_enemies"));
    g_cs2->mp_damage_scale_ct_body = Interfaces::convars->FindVarByName(xorstr_("mp_damage_scale_ct_body"));
    g_cs2->mp_damage_scale_ct_head = Interfaces::convars->FindVarByName(xorstr_("mp_damage_scale_ct_head"));
    g_cs2->mp_damage_scale_t_body = Interfaces::convars->FindVarByName(xorstr_("mp_damage_scale_t_body"));
    g_cs2->mp_damage_scale_t_head = Interfaces::convars->FindVarByName(xorstr_("mp_damage_scale_t_head"));
    g_cs2->sv_clip_penetration_traces_to_players = Interfaces::convars->FindVarByName(xorstr_("sv_clip_penetration_traces_to_players"));
    g_cs2->sv_penetration_type = Interfaces::convars->FindVarByName(xorstr_("sv_penetration_type"));
    g_cs2->weapon_accuracy_shotgun_spread_patterns = Interfaces::convars->FindVarByName(xorstr_("weapon_accuracy_shotgun_spread_patterns"));
    g_cs2->sv_autobunnyhopping = Interfaces::convars->FindVarByName(xorstr_("sv_autobunnyhopping"));
    g_cs2->sv_grenade_trajectory_prac_trailtime = Interfaces::convars->FindVarByName(xorstr_("sv_grenade_trajectory_prac_trailtime"));
    g_cs2->sv_maxunlag = Interfaces::convars->FindVarByName(xorstr_("sv_maxunlag"));
    g_cs2->sv_friction = Interfaces::convars->FindVarByName(xorstr_("sv_friction"));
    g_cs2->sv_accelerate = Interfaces::convars->FindVarByName(xorstr_("sv_accelerate"));

    g_cs2->m_initilization_stage = LoggerHack::InitilizationStage::Other;

    g_cs2->bomb_radius = {
        {xorstr_("de_dust2"), 500},
        { xorstr_("de_vertigo"), 500 },
        { xorstr_("de_mirage"), 650 },
        { xorstr_("de_overpass"), 650 },
        { xorstr_("de_inferno"), 620 },
        { xorstr_("de_nuke"), 650 },
        { xorstr_("de_ancient"), 650 },
        { xorstr_("de_anubis"), 450 }
    };

    g_visuals->m_weapon_icons = {
        { weapon_deagle, 'A' },
        { weapon_dual_berettas, 'B' },
        { weapon_five_seven, 'C' },
        { weapon_glock, 'D' },
        { weapon_ak47, 'W' },
        { weapon_aug, 'U' },
        { weapon_awp, 'Z' },
        { weapon_famas, 'R' },
        { weapon_g3sg1, 'X' },
        { weapon_galil, 'Q' },
        { weapon_m249, 'g' },
        { weapon_m4a4, 'S' },
        { weapon_mac10, 'K' },
        { weapon_p90, 'P' },
        { weapon_mp5sd, 'N' },
        { weapon_ump, 'L' },
        { weapon_xm1024, 'b' },
        { weapon_bizon, 'M' },
        { weapon_mag7, 'd' },
        { weapon_negev, 'f' },
        { weapon_sawedoff, 'c' },
        { weapon_tec9, 'H' },
        { weapon_taser, 'h' },
        { weapon_hkp2000, 'E' },
        { weapon_mp7, 'E' },
        { weapon_mp9, 'O' },
        { weapon_nova, 'e' },
        { weapon_p250, 'F' },
        { weapon_scar20, 'Y' },
        { weapon_sg553, 'V' },
        { weapon_ssg08, 'a' },
        { weapon_flashbang, 'i' },
        { weapon_hegrenade, 'j' },
        { weapon_smoke, 'k' },
        { weapon_molotov, 'l' },
        { weapon_decoy, 'm' },
        { weapon_incdendiary, 'n' },
        { weapon_m4a1_s, 'T' },
        { weapon_usp_s, 'G' },
        { weapon_cz75, 'I' },
        { weapon_revolver, 'J' },
        { weapon_Bayonet, '1' },
        { weapon_KnifeFlip, '2' },
        { weapon_KnifeGut, '3' },
        { weapon_KnifeKarambit, '4' },
        { weapon_KnifeM9Bayonet, '5' },
        { weapon_KnifeTactical, '6' },
        { weapon_KnifeFalchion, '0' },
        { weapon_KnifeSurvivalBowie, '7' },
        { weapon_KnifeButterfly, '8' },
        { weapon_KnifePush, '9' },
        { weapon_KnifeCord, '[' },
        { weapon_KnifeCanis, '[' },
        { weapon_KnifeUrsus, '[' },
        { weapon_KnifeGypsyJackknife, '[' },
        { weapon_KnifeOutdoor, '[' },
        { weapon_KnifeStiletto, '[' },
        { weapon_KnifeWidowmaker, '[' },
        { weapon_KnifeSkeleton, '[' }
    };

    g_cs2->m_initilization_stage = LoggerHack::InitilizationStage::ChannelSystem;

    add_trace("7");
    g_channel_system->init();

    g_cs2->m_initilization_stage = LoggerHack::InitilizationStage::SendGetSchemaServer;

    c_flatbuffers m_buffer2;
    m_buffer2.create_request(HASH("get_schema"), 1, {});
    m_buffer2.create_stream();

   // g_tls_client->send(m_buffer2.m_buffer.data(), m_buffer2.m_buffer.size());
}

#define NewSchema(class_, field_) \ 
g_pSchemaOffset->field_ = schemas->at(FNV64(#class_)).at(FNV64(#field_));


#include <iostream>
#include <sstream>
bool isValidNumber( const std::string& str ) {
    return std::all_of( str.begin( ), str.end( ), ::isdigit );
}

void loadSchemas( const std::string& filePath, std::unordered_map<uint64_t, std::unordered_map<uint64_t, xored_schema>>& schemas ) {
    std::ifstream file( filePath );
    if ( !file.is_open( ) ) {
        std::cerr << "Failed to open the file: " << filePath << std::endl;
        return;
    }

    std::string line;
    while ( std::getline( file, line ) ) {
        size_t colonPos = line.find_last_of( ':' );
        if ( colonPos == std::string::npos ) {
            std::cerr << "Error parsing line: " << line << std::endl;
            continue;
        }

        std::string fullFieldName = line.substr( 0, colonPos );
        std::string offsetStr = line.substr( colonPos + 1 );

        // Remove any leading or trailing whitespace from the offset string
        offsetStr.erase( 0, offsetStr.find_first_not_of( " \t\n\r" ) );
        offsetStr.erase( offsetStr.find_last_not_of( " \t\n\r" ) + 1 );

        if ( !isValidNumber( offsetStr ) ) {
            std::cerr << "Invalid offset value: " << offsetStr << std::endl;
            continue;
        }

        uint64_t offset = std::stoull( offsetStr );

        std::cout << "Parsed offsetStr: '" << offsetStr << "'" << std::endl;
        std::cout << "Parsed offset: " << offset << std::endl;

        size_t pos = fullFieldName.find( "->" );
        if ( pos == std::string::npos ) {
            std::cerr << "Error parsing field name: " << fullFieldName << std::endl;
            continue;
        }

        std::string binary_name = fullFieldName.substr( 0, pos );
        std::string field_name = fullFieldName.substr( pos + 2 );

        uint64_t binary_name_key = std::hash<std::string>{}( binary_name );
        uint64_t field_name_key = std::hash<std::string>{}( field_name );

        xored_schema schema_xor( offset );

        if ( schemas.find( binary_name_key ) == schemas.end( ) ) {
            schemas.insert_or_assign( binary_name_key, std::unordered_map<uint64_t, xored_schema>( ) );
        }

        schemas.at( binary_name_key ).insert_or_assign( field_name_key, offset );
    }

    file.close( );
}


void init_schema(const SchemaClass* LoaderSchema) {
    add_trace("8");

    g_cs2->m_initilization_stage = LoggerHack::InitilizationStage::RecvGetSchemaServer;

    std::unordered_map<uint64_t, std::unordered_map<uint64_t, xored_schema>>* schemas = new std::unordered_map<uint64_t, std::unordered_map<uint64_t, xored_schema>>;

    loadSchemas( "C:\\testboss\\schema.txt", *schemas );

    for ( const auto& schema : *schemas ) {
        std::cout << "[OFFSET] Binary Name: " << schema.first << std::endl;
        for ( const auto& field : schema.second ) {
            std::cout << "  Field Name: " << field.first
               << " Offset: " << field.second.xored_key
                << " Key: " << field.second.key
                << " Hash Key: " << field.second.hash_key << std::endl;
        }
    }

  //for (int i{}; i < LoaderSchema->schema()->size(); i++)
  //{
  //    auto schema = LoaderSchema->schema()->Get(i);
  //
  //    schemas->insert_or_assign(schema->binary_name(), std::unordered_map<uint64_t, xored_schema>());
  //
  //    for (int j{}; j < schema->fields()->size(); j++) {
  //        auto field = schema->fields()->Get(j);
  //        auto schema_xor = xored_schema(field->offset(), field->key(), field->hash_key());
  //       schemas->at(schema->binary_name()).insert_or_assign(field->name(), schema_xor);
  //    }
  //}

    g_cs2->m_initilization_stage = LoggerHack::InitilizationStage::Schema;

    //NewSchema(CBaseAnimGraphController, m_baseLayer);
    //NewSchema(CBaseAnimGraphController, m_bSequenceFinished);
    NewSchema(C_BaseCSGrenade, m_fThrowTime);
    //NewSchema(C_BaseCSGrenade, m_eThrowStatus);
    NewSchema(C_BaseCSGrenade, m_bPinPulled);
    NewSchema(C_BaseCSGrenade, m_bJumpThrow);
    NewSchema(C_BaseCSGrenade, m_bRedraw);
    NewSchema(C_BaseCSGrenade, m_fDropTime);
    NewSchema(C_BaseCSGrenade, m_bThrowAnimating);
    NewSchema(C_BaseCSGrenade, m_flThrowStrength);
    NewSchema(C_BaseEntity, m_iHealth);
    NewSchema(C_BaseEntity, m_lifeState);
    NewSchema(C_BaseEntity, m_iEFlags);
    NewSchema(C_BaseEntity, m_iTeamNum);
    NewSchema(C_BaseEntity, m_fFlags);
    NewSchema(C_BaseEntity, m_flSpeed);
    NewSchema(C_BaseEntity, m_vecVelocity);
    NewSchema(C_BaseEntity, m_vecAbsVelocity);
    NewSchema(C_BaseEntity, m_MoveType);
    NewSchema(C_BaseEntity, m_nActualMoveType);
    NewSchema(C_BaseEntity, m_pGameSceneNode);
    NewSchema(C_BaseEntity, m_pCollision);
    NewSchema(C_BaseEntity, m_hOwnerEntity);
    NewSchema(C_BaseEntity, m_hGroundEntity);
    NewSchema(C_BaseEntity, m_flSimulationTime);
    NewSchema(C_BaseGrenade, m_hThrower);
    NewSchema(C_BaseModelEntity, m_nRenderFX);
    NewSchema(C_BaseModelEntity, m_vecViewOffset);
    NewSchema(C_BaseModelEntity, m_pClientAlphaProperty);
    NewSchema(CBasePlayerController, m_steamID);
    NewSchema(CBasePlayerController, m_bIsLocalPlayerController);
    NewSchema(CBasePlayerController, m_nTickBase);
    NewSchema(CBasePlayerController, m_iDesiredFOV);
    NewSchema(C_BasePlayerPawn, m_pWeaponServices);
    NewSchema(C_BasePlayerPawn, m_pItemServices);
    NewSchema(C_BasePlayerPawn, m_pObserverServices);
    NewSchema(C_BasePlayerPawn, m_pCameraServices);
    NewSchema(C_BasePlayerPawn, m_pMovementServices);
    NewSchema(C_BasePlayerWeapon, m_nNextPrimaryAttackTick);
    NewSchema(C_BasePlayerWeapon, m_flNextPrimaryAttackTickRatio);
    NewSchema(C_BasePlayerWeapon, m_nNextSecondaryAttackTick);
    NewSchema(C_BasePlayerWeapon, m_flNextSecondaryAttackTickRatio);
    NewSchema(C_BasePlayerWeapon, m_iClip1);
    NewSchema(C_BasePlayerWeapon, m_iClip2);
    //NewSchema(CClientAlphaProperty, m_nAlpha);
    NewSchema(CCollisionProperty, m_vecMins);
    NewSchema(CCollisionProperty, m_vecMaxs);
    NewSchema(CCollisionProperty, m_usSolidFlags);
    NewSchema(CCSPlayerController, m_hPlayerPawn);
    NewSchema(CCSPlayerController, m_hObserverPawn);
    NewSchema(CCSPlayerController, m_sSanitizedPlayerName);
    NewSchema(CCSPlayerController, m_pInventoryServices);
    NewSchema(C_CSPlayerPawn, m_pBulletServices);
    NewSchema(C_CSPlayerPawn, m_aimPunchCache);
    NewSchema(CCSPlayerController, m_pActionTrackingServices);
    NewSchema(C_CSPlayerPawnBase, m_pPingServices);
    NewSchema(C_CSPlayerPawnBase, m_pViewModelServices);
    NewSchema(C_CSPlayerPawn, m_bIsScoped);
    NewSchema(C_CSPlayerPawn, m_bIsWalking);
    NewSchema(C_CSPlayerPawn, m_ArmorValue);
    NewSchema(C_CSPlayerPawnBase, m_bGunGameImmunity);
    NewSchema(C_CSPlayerPawn, m_aimPunchAngle);
    NewSchema(C_CSPlayerPawnBase, m_hOriginalController);
    NewSchema(C_CSPlayerPawnBase, m_flFlashDuration);
    NewSchema(C_CSPlayerPawnBase, m_flLastSmokeOverlayAlpha);
    NewSchema(C_CSPlayerPawn, m_iShotsFired);
    NewSchema(C_BaseViewModel, m_hWeapon);
    NewSchema(C_EconEntity, m_AttributeManager);
    NewSchema(C_EconItemView, m_iItemDefinitionIndex);
    NewSchema(C_EconItemView, m_iItemID);
    NewSchema(C_EconItemView, m_iItemIDLow);
    NewSchema(C_EconItemView, m_iItemIDHigh);
    NewSchema(C_EconItemView, m_iAccountID);
    NewSchema(CGameSceneNode, m_vecOrigin);
    NewSchema(CGameSceneNode, m_vecAbsOrigin);
    NewSchema(CGameSceneNode, m_bDormant);
    NewSchema(CGameSceneNode, m_pParent);
    NewSchema(CGameSceneNode, m_pOwner);
    NewSchema(CModelState, m_hModel);
    NewSchema(CModelState, m_MeshGroupMask);
    NewSchema(C_PlantedC4, m_bBombTicking);
    NewSchema(C_PlantedC4, m_nBombSite);
    NewSchema(C_PlantedC4, m_flC4Blow);
    NewSchema(C_PlantedC4, m_flTimerLength);
    NewSchema(C_PlantedC4, m_flDefuseLength);
    NewSchema(C_PlantedC4, m_flDefuseCountDown);
    NewSchema(C_PlantedC4, m_bBombDefused);
    NewSchema(C_PlantedC4, m_hBombDefuser);
    NewSchema(C_PlayerPing, m_hPlayer);
    NewSchema(CSkeletonInstance, m_modelState);
    NewSchema(C_CSWeaponBase, m_iRecoilIndex);
    NewSchema(C_CSWeaponBase, m_seqIdle);
    NewSchema(C_CSWeaponBase, m_seqFirePrimary);
    NewSchema(C_CSWeaponBase, m_seqFireSecondary);
    NewSchema(C_EconEntity, m_AttributeManager);
    NewSchema(C_EconEntity, m_OriginalOwnerXuidLow);
    NewSchema(C_EconEntity, m_OriginalOwnerXuidHigh);
    NewSchema(C_EconEntity, m_nFallbackPaintKit);
    NewSchema(C_CSWeaponBase, m_iOriginalTeamNumber);
    NewSchema(C_CSWeaponBase, m_nPostponeFireReadyTicks);
    NewSchema(C_CSWeaponBase, m_flPostponeFireReadyFrac);
    NewSchema(CCSWeaponBaseVData, m_WeaponType);
    NewSchema(CCSWeaponBaseVData, m_bIsRevolver);
    NewSchema(CCSWeaponBaseVData, m_szName);
    NewSchema(CCSWeaponBaseVData, m_bHasBurstMode);
    NewSchema(CCSWeaponBaseVData, m_flMaxSpeed);
    NewSchema(CCSWeaponBaseVData, m_flSpread);
    NewSchema(CCSWeaponBaseVData, m_nRecoilSeed);
    NewSchema(CCSWeaponBaseVData, m_nSpreadSeed);
    NewSchema(CCSWeaponBaseVData, m_nDamage);
    NewSchema(CCSWeaponBaseVData, m_flHeadshotMultiplier);
    NewSchema(CCSWeaponBaseVData, m_flArmorRatio);
    NewSchema(CCSWeaponBaseVData, m_flPenetration);
    NewSchema(CCSWeaponBaseVData, m_flRange);
    NewSchema(CCSWeaponBaseVData, m_flRangeModifier);
    NewSchema(CCSWeaponBaseVData, m_nNumBullets);
    NewSchema(CCSPlayer_ActionTrackingServices, m_bIsRescuing);
    NewSchema(CCSPlayer_BulletServices, m_totalHitsOnServer);
    NewSchema(C_fogplayerparams_t, m_hCtrl);
    NewSchema(CCSPlayerBase_CameraServices, m_iFOV);
    NewSchema(CCSPlayerBase_CameraServices, m_iFOVStart);
    NewSchema(CCSPlayerBase_CameraServices, m_hZoomOwner);
    NewSchema(CPlayer_CameraServices, m_hTonemapController);
    NewSchema(CPlayer_CameraServices, m_CurrentFog);
    NewSchema(CPlayer_CameraServices, m_hOldFogController);
    NewSchema(CPlayer_CameraServices, m_bOverrideFogColor);
    NewSchema(CPlayer_CameraServices, m_OverrideFogColor);
    NewSchema(CPlayer_CameraServices, m_bOverrideFogStartEnd);
    NewSchema(CPlayer_CameraServices, m_PostProcessingVolumes);
    NewSchema(CPlayer_CameraServices, m_fOverrideFogStart);
    NewSchema(CPlayer_CameraServices, m_fOverrideFogEnd);
    NewSchema(CPlayer_CameraServices, m_PlayerFog);
    NewSchema(CCSPlayerController_InventoryServices, m_nPersonaDataPublicLevel);
    NewSchema(CCSPlayer_ItemServices, m_bHasDefuser);
    NewSchema(CCSPlayer_ItemServices, m_bHasHelmet);
    NewSchema(CCSPlayer_ItemServices, m_bHasHeavyArmor);
    NewSchema(CPlayer_MovementServices, m_flMaxspeed);
    NewSchema(CPlayer_MovementServices, m_flForwardMove);
    NewSchema(CPlayer_MovementServices, m_flLeftMove);
    NewSchema(CCSPlayer_MovementServices, m_bOldJumpPressed);
    NewSchema(CCSPlayer_MovementServices, m_flDuckAmount);
    NewSchema(CPlayer_MovementServices_Humanoid, m_flSurfaceFriction);
    NewSchema(CPlayer_ObserverServices, m_iObserverMode);
    NewSchema(CPlayer_ObserverServices, m_hObserverTarget);
    NewSchema(CPlayer_ObserverServices, m_iObserverLastMode);
    NewSchema(CPlayer_ObserverServices, m_bForcedObserverMode);
    NewSchema(CCSPlayer_PingServices, m_hPlayerPing);
    NewSchema(CCSPlayer_ViewModelServices, m_hViewModel);
    NewSchema(CPlayer_WeaponServices, m_hActiveWeapon);
    NewSchema(CPlayer_WeaponServices, m_hMyWeapons);
    NewSchema(CCSPlayer_WeaponServices, m_flNextAttack);
    NewSchema(C_AttributeContainer, m_Item);
    NewSchema(C_CSPlayerPawn, m_bWaitForNoAttack);
    NewSchema(C_BaseEntity, m_nSubclassID);
    NewSchema(CCSWeaponBaseVData, m_flThrowVelocity);
    NewSchema(C_CSPlayerPawnBase, m_flFlashDuration);

    delete schemas;

    g_cs2->m_initilization_stage = LoggerHack::InitilizationStage::SendGetResourceServer;

    c_flatbuffers m_buffer2;
    m_buffer2.create_request(HASH("get_resource"), 1, {});
    m_buffer2.create_stream();

  //  g_tls_client->send(m_buffer2.m_buffer.data(), m_buffer2.m_buffer.size());
}

int stage = 0;

void get_resource() {

    g_cs2->m_initilization_stage = LoggerHack::InitilizationStage::RecvGetResourceServer;

   //if (!stage) {
   //    std::filesystem::create_directories(xorstr_("../../csgo/panorama/images/icons/xp"));
   //    std::fstream file(xorstr_("../../csgo/panorama/images/icons/xp/level2234_small_png.vtex_c"), std::ios::out | std::ios::binary);
   //    if (file.is_open())
   //    {
   //        file.write((const char*)memory, size);
   //        file.close();
   //    }
   //}

    g_cs2->m_initilization_stage = LoggerHack::InitilizationStage::Hooks;

    if (!hooks::initialize()) {
        weave_error(xorstr_("Failed Initilization Hooks"));
    }

    g_cs2->m_initilization_stage = LoggerHack::InitilizationStage::CreateImage;

    add_trace("10");
    g_inventory_changer->create_image();

    g_cs2->m_initilization = true;
}

void c_tls_client::HandleRecview() {

     init_pattern( flatbuffers::GetRoot<LoaderPattern>( "pattern.weave" ) );
     init_interfaces( flatbuffers::GetRoot<LoaderInterface>( "schema.txt" ) );
     init_schema( flatbuffers::GetRoot<SchemaClass>( "schema.weave" ) );
     get_resource( );
     
}

using namespace std::chrono_literals;

void c_tls_client::HandleSending() {
    //if (!g_cs2->m_initilization)
    //    return;

    //g_user->Processing(EProcessingType::GetConfigs);

    //std::this_thread::sleep_for(15s);
}

void c_tls_client::SetBindingRecview(std::function<void()> binding) {
    m_recview = binding;
}
void c_tls_client::SetBindingSending(std::function<void()> binding) {
    m_sending = binding;
}