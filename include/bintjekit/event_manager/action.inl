/*!
 * @author bintjeman
 * @date 18.07.25
 * @name action.inl
 */

#ifndef BINTJEKIT_EVENT_ACTION_INL
#define BINTJEKIT_EVENT_ACTION_INL
#pragma once
namespace bnjkit::event {
    template<typename ... Args>
Action<Args...>::Action(std::string  name, const Callback& callback): m_name(std::move(name)), m_callback(callback) {}
    template<typename ... Args>
    void Action<Args...>::execute(Args... args) const {
        m_callback(std::forward<Args>(args)...);
    }
    template<typename ... Args>
    const std::string& Action<Args...>::get_name() const {
        return m_name;
    }
}
#endif // BINTJEKIT_EVENT_ACTION_INL
