#pragma once

#include "Auth.hpp"
#include "detail/Contract.hpp"
#include "detail/ContractFactory.hpp"
#include "detail/ProfileURI.hpp"

namespace BitProfile{


class Profile : public Contract
{
    public:
        typedef ProfileURI URI;

    public:
        Profile(Provider &provider, const std::string &addres);
        Profile(Provider &provider, const std::string &addres, const ProfileURI &uri);

        template<class Permit>
        bool set(const std::string &key, const std::string &value, const std::string &authData, const Permit &);

        template<class Permit>
        bool clear(const std::string &key, const std::string &authData, const Permit &);

        template<class Permit>
        bool setPaymentAddress(const address_t &, const std::string &authData, const Permit &);

        template<class Permit>
        bool transfer(const address_t &, const std::string &authData, const Permit &);

        template<class Permit>
        txid_t setPermission(const std::string &key, BitProfile::Auth::Permission, const std::string &authData, const Permit &);

        template<class Permit>
        txid_t kill(const std::string &authData, const Permit &);

        template<class Permit, class Callback>
        void set(const std::string &key, const std::string &value, const std::string &authData, const Permit &, const Callback &);

        template<class Permit, class Callback>
        void clear(const std::string &key, const std::string &authData, const Permit &, const Callback &);

        template<class Permit, class Callback>
        void setPaymentAddress(const address_t &, const std::string &authData, const Permit &, const Callback &);

        template<class Permit, class Callback>
        void transfer(const address_t &, const std::string &authData, const Permit &, const Callback &);




        std::string get(const std::string &key) const;
        address_t getPaymentAddress() const;
        bool authenticate(const address_t &, BitProfile::Auth::Permission);
        address_t getAuth() const;
        const URI & getURI() const;

    private:
        bool validateKey(const std::string &key) const;
        bool checkKey(std::string key, std::string value);
        bool checkOwner(address_t);

    private:
        URI _uri;
};


DECLARE_CONTRACT_FACTORY(ProfileFactory, Profile, ContractCode::Profile);

}

#include "Profile.ipp"
