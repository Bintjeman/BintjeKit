/*!
 * @file iactionreceiver_interface.cppm
 * @author bintjeman
 * @date 08.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
export module bik.common:action_receiver;
namespace bik::common {
    export class BaseIActionReceiver {
    public:
        virtual ~BaseIActionReceiver() = default;
        virtual void on_close_window() = 0; // Événement abstrait : demande de fermeture
    };
}
