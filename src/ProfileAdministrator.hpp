#pragma once

#include "Profile.hpp"
#include "Registrar.hpp"
#include "AddressAuth.hpp"
#include "AddressAuthKey.hpp"
#include "ProfileDescriptor.hpp"
#include "Resolver.hpp"

#include "detail/types.hpp"
#include "detail/KeyAdapter.hpp"


namespace BitProfile{


class ProfileAdministrator
{
    public:
        template<class Key>
        ProfileAdministrator(const Profile &, const Key &);

        ProfileAdministrator(const Profile &, const KeyAdapter &);

        void setGasPrice(const BigInt &);
        void setGasLimit(const BigInt &);

        bool set(const std::string &key, const std::string &value, const std::string &password);

        template<class Callback>
        void set(const std::string &key, const std::string &value, const std::string &password, const Callback &);

        bool setPaymentAddress(const address_t &, const std::string &password);

        template<class Callback>
        void setPaymentAddress(const address_t &, const std::string &password, const Callback &);

        bool changeAuth(const AddressAuth &, const std::string &password);

        template<class Callback>
        void changeAuth(const AddressAuth &, const std::string &password, const Callback &);


        bool link(Registrar &, const std::string &name, const std::string &password);
        bool unlink(Registrar &, const std::string &password);

        template<class Callback>
        void link(Registrar &, const std::string &name, const std::string &password, const Callback &);

        template<class Callback>
        void unlink(Registrar &, const std::string &password, const Callback &);

        bool move(Registrar &, const std::string &name, const std::string &password);

        template<class Callback>
        void move(Registrar &, const std::string &name, const std::string &password, const Callback &);

        static ProfileAdministrator CreateProfile(Registrar &, const std::string &name, const std::string &password);
        static ProfileAdministrator CreateProfile(Registrar &, const std::string &name, const address_t &, const std::string &password);

        template<class Callback>
        static void CreateProfile(Registrar &, const std::string &name, const std::string &password, const Callback &);

        template<class Callback>
        static void CreateProfile(Registrar &, const std::string &name, const address_t &, const std::string &password, const Callback &);

        template<class Key>
        static ProfileAdministrator CreateProfile(Registrar &, const std::string &name, const Key &, const std::string &password);

        template<class Key, class Callback>
        static void CreateProfile(Registrar &, const std::string &name, const Key &, const std::string &password, const Callback &);

        static ProfileAdministrator FromDescriptor(Provider &, const ProfileDescriptor &);

        const KeyAdapter & getKey() const;
        const Profile & getProfile() const;
        bool isNull() const;

    private:
        template<class Callback, class Key>
        class ChangeAuthCallback;

        template<class Callback, class Key>
        class CreateProfileCallback;

        template<class Callback>
        class RenameProfileCallback;

    private:
        Profile _profile;
        KeyAdapter _key;
};


}

#include "ProfileAdministrator.ipp"
