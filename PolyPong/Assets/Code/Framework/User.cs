using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum UserType
{
    UNDEFINED,
    SERVER,
    CLIENT
}

public abstract class User
{
    public UserType mUserType { get; private set; } = UserType.UNDEFINED;
    public string mUsername { get; private set; } = "Noob0";
    public int mPort { get; private set; } = 5555;

    public User(UserType userType, string username, int port)
    {
        mUserType = userType;
        mUsername = username;
        mPort = port;
    }
}
