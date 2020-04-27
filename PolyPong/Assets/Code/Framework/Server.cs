using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Server : User
{
    public int mMaxUserCount { get; private set; } = 10;

    public Server(int port, int maxUserCount) : base(UserType.SERVER, "Server", port)
    {
        mMaxUserCount = maxUserCount;
    }
}
