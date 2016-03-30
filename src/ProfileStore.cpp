#include "ProfileStore.hpp"


namespace BitProfile{


ProfileStore::ProfileStore() :
    _path(getDefaultPath(Main_Net))
{
    createIfNotExists();
}


ProfileStore::ProfileStore(const char *path) :
    _path(fs::absolute(path))
{
    createIfNotExists();
}


ProfileStore::ProfileStore(Network net) :
    _path(getDefaultPath(net))
{
    createIfNotExists();
}


ProfileStore::ProfileStore(const fs::path &path) :
    _path(path)
{
    createIfNotExists();
}


fs::path ProfileStore::getDefaultPath(Network net) const
{
    fs::path path;
#if  defined(__APPLE_OS__)
    path = getenv("HOME");
    path /= "Library/BitProfile";
#elif defined(__LINUX_OS__)
    path = getenv("HOME");
    path /= ".bitprofile";
#elif defined(__WINDOWS_OS__)
    char appdata[1024] = "";
    if (SHGetSpecialFolderPathA(NULL, appdata, CSIDL_APPDATA, true))
    {
        path = appdata;
    }
    else
    {
        path = getenv("HOMEPATH");
    }
    path /= "BitProfile";
#endif

    if(net==Test_Net)
    {
        path /= "testnet";
    }

    path /= "profiles";

    return path;
}

void ProfileStore::createIfNotExists()
{
    boost::filesystem::create_directories(_path);
}

ProfileStore::Iterator ProfileStore::begin() const
{
    return Iterator(fs::directory_iterator(_path));
}


ProfileStore::Iterator ProfileStore::end() const
{
    return Iterator(fs::directory_iterator());
}

ProfileStore::Iterator ProfileStore::find(const std::string &uri) const
{
    return find(uri.c_str());
}

ProfileStore::Iterator ProfileStore::find(const Profile::URI &uri) const
{
    return find(uri.toString());
}

ProfileStore::Iterator ProfileStore::find(const char *uri) const
{
    Iterator it = begin();
    for(; it!= end(); ++it)
    {
        if(it.path().stem()=="uri")
        {
            break;
        }
    }
    return it;
}


bool ProfileStore::contains(const char *uri) const
{
    return fs::exists(makeProfilePath(uri));
}


bool ProfileStore::changeProfileURI(const Profile::URI &oldURI, const Profile::URI &newURI)
{
    return changeProfileURI(oldURI.toString(), newURI);
}


bool ProfileStore::changeProfileURI(const std::string &oldURI, const Profile::URI &newURI)
{
    fs::path oldPath = makeProfilePath(oldURI);
    fs::path newPath = makeProfilePath(newURI.toString());

    if(!fs::exists(oldPath))
    {
        return false;
    }

    std::fstream file(oldPath.string().c_str());
    ProfileDescriptor descriptor;
    file>>descriptor;
    descriptor.setURI(newURI);
    file<<descriptor;
    fs::rename(oldPath, newPath);
    return true;
}

bool ProfileStore::insert(const ProfileDescriptor &descriptor)
{
    fs::path path = makeProfilePath(descriptor.getURI());
    std::ofstream stream(path.string().c_str(), std::ofstream::trunc);
    stream<<descriptor;
    return (bool)stream;
}


bool ProfileStore::remove(const Profile::URI &uri)
{
    return remove(uri.toString());
}


bool ProfileStore::remove(const std::string &uri)
{
    return fs::remove(makeProfilePath(uri));
}


fs::path ProfileStore::makeProfilePath(const std::string &uri) const
{
    std::string filename = uri;
    size_t pos = filename.find(':');
    if(pos!=std::string::npos)
    {
        filename.replace(pos, 1, 1, '_');
    }
    filename += ".bp";
    fs::path path = _path;
    path /= filename;
    return path;
}


}
