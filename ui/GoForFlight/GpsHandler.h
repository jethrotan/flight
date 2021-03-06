#ifndef GPS_HANDLER_H
#define GPS_HANDLER_H

#include "StatusHandler.h"
#include "../../LCM/mav/gps_data_t.hpp"

class GpsHandler : public StatusHandler
{
    public:
        GpsHandler() : StatusHandler("") {
        }
        ~GpsHandler() {}

        void handleMessage(const lcm::ReceiveBuffer* rbuf,
                           const std::string& chan,
                           const mav::gps_data_t* msg) {

            if (msg->utime > last_utime2_ && msg->gps_lock >= 3) {
                SetStatus(true, msg->utime);
            } else {
                SetStatus(false, msg->utime);
            }

            last_utime2_ = last_utime_;
            last_utime_ = msg->utime;

            last_num_sats_ = msg->numSatellites;

        }

        void Update() {
            if (last_num_sats_ >= 0) {
                SetText(std::string(wxString::Format("GPS: %s (Sats: %d)", GetStatusString(GetStatus()), last_num_sats_)));
            } else {
                SetText(std::string(wxString::Format("GPS: %s (Sats: --)", GetStatusString(GetStatus()))));
            }

            SetColour(GetColour(GetStatus()));

        }

    private:
        long last_utime_ = -1;
        long last_utime2_ = -1;
        int last_num_sats_ = -1;


};

#endif // LOG_SIZE_HANDLER_HPP

