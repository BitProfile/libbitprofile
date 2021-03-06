
#include <iostream>

#include "ethrpc/Provider.hpp"
#include "bitprofile/Resolver.hpp"

#include "utils/UnlockAccount.hpp"

int main(int argc, char **argv)
{
    if(argc<2)
    {
        std::cout<<"usage : find_profile [uri]"<<std::endl;
        return 1;
    }

    Ethereum::Connector::Provider provider;
    provider.connect(Ethereum::Connector::Test_Net);

    BitProfile::Resolver resolver(provider, BitProfile::Test_Net);
    BitProfile::Profile profile = resolver.lookupProfile(argv[1]);

    if(profile.isNull())
    {
        std::cout<<"profile not found"<<std::endl;
    }
    else
    {
        std::cout<<"profile found : "<<profile.getAddress()<<std::endl;
        std::cout<<"uri : "<<argv[1]<<std::endl;
    }




    return 0;
}

