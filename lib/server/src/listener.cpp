#include "listener.hpp"


Listener::Listener(
        boost::asio::io_context& ioc,
        boost::asio::ip::tcp::endpoint endpoint,
        std::shared_ptr<std::string const> const& doc_root)
        : ioc_(ioc), 
          acceptor_(boost::asio::make_strand(ioc)),
          doc_root_(doc_root) {
        
        boost::beast::error_code ec;

        // Open the acceptor
        acceptor_.open(endpoint.protocol(), ec);
        if(ec)
        {
            fail(ec, "open");
            return;
        }

        // Allow address reuse
        acceptor_.set_option(boost::asio::socket_base::reuse_address(true), ec);
        if(ec)
        {
            fail(ec, "set_option");
            return;
        }

        // Bind to the server address
        acceptor_.bind(endpoint, ec);
        if(ec)
        {
            fail(ec, "bind");
            return;
        }

        // Start listening for connections
        acceptor_.listen(
            boost::asio::socket_base::max_listen_connections, ec);
        if(ec)
        {
            fail(ec, "listen");
            return;
        }
}


void Listener::do_accept() {
    // The new connection gets its own strand
    acceptor_.async_accept(
        boost::asio::make_strand(ioc_),
        boost::beast::bind_front_handler(
            &Listener::on_accept,
            shared_from_this()));
}

void Listener::on_accept(boost::beast::error_code ec, boost::asio::ip::tcp::socket socket) {
    if(ec)
    {
        fail(ec, "accept");
    }
    else
    {
        // Create the session and run it
        std::make_shared<Session>(
            std::move(socket),
            doc_root_)->run();
    }

    // Accept another connection
    do_accept();
}