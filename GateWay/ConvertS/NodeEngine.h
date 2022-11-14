#include <boost>

struct interval_timer {
    interval_timer(boost::asio::io_context& io, Clock::duration i, Callback cb)
        : interval(i), callback(cb), timer(io)
    {}

    void run() {
        timer.expires_from_now(interval);
        timer.async_wait([=](error_code ec) {
            if (!ec && callback())
                run();
        });
    }

    void stop() {
        timer.cancel();
    }

  private:
    Clock::duration const interval; 
    Callback callback;
    boost::asio::high_resolution_timer timer;
};