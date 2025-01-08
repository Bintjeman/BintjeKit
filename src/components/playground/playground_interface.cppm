/*!
 * @file simulation_interface.cppm
 * @author bintjeman
 * @date 08.01.25
 * 
 * @brief 
 *
 * @details 
 *
 */
export module bik.playground:interface;
namespace bik::playground {
    export class BasePlayGround {
    public:
        BasePlayGround();
        virtual ~BasePlayGround();

        virtual void configure();
        virtual void initialize();
        virtual void update();
        virtual void finalize();
    };

}
