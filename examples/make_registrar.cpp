
#include <iostream>

#include "ethrpc/Provider.hpp"
#include "ethrpc/Wallet.hpp"

#include "bitprofile/MasterRegistrar.hpp"

int main(int argc, char **argv)
{

    if(argc<2)
    {
        std::cout<<"usage : make_registrar [password]"<<std::endl;
        return 1;
    }

    Ethereum::Connector::Provider provider;
    provider.connect();

    Ethereum::Connector::Wallet wallet(provider);
    if(!wallet.unlockAccount(wallet.getCoinBase(), argv[1]))
    {
        std::cout<<"failed to unlock default account"<<std::endl;
        return 2;
    }

    BitProfile::MasterRegistrar registrar(provider, BitProfile::MasterRegistrar::Test_Net);

    std::cout<<"creating registrar : "<<registrar.create()<<std::endl;
    std::cout<<"beta : "<<registrar.isBeta()<<std::endl;
    std::cout<<"size : "<<registrar.getSize()<<std::endl;

    return 0;
}

