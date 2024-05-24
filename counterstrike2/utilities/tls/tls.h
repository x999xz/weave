#pragma once

#include <wolfssl/ssl.h>
#include <regex>
#include <mutex>
#include <functional>


class c_tls_client {
public:
    bool connect();
    void reconnect();
    void send(const void* buffer, int size);
    std::string* read();
    static void HandleRecview();
    static void HandleSending();
    void SetBindingRecview(std::function<void()> binding);
    void SetBindingSending(std::function<void()> binding);

protected:
    int m_socket;
    WOLFSSL_CTX* m_ssl_ctx;
    WOLFSSL* m_server_ssl;
    wolfSSL_Mutex m_mutex;
public:
	bool has_reconnection = false;
    bool m_connected = false;
    bool m_should_request = false;
    bool m_wait = false;

    std::function<void()> m_recview;
    std::function<void()> m_sending;


    bool m_keys_initialized;
};

inline auto g_tls_client = std::make_unique<c_tls_client>();