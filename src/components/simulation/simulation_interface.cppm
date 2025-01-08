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
export module bik.simulation:interface;
namespace bik::simulation {
    export class BaseSimulation {
    public:
        BaseSimulation();
        virtual ~BaseSimulation();

        virtual void configure();
        virtual void initialize();
        virtual void update();
        virtual void finalize();
    };

}
