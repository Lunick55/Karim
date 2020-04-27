using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Persistent : Singleton<Persistent>
{
    public static GameObject Object;
    public ClientConnectionInfo ClientInfo;
    public User CurrentUser;
    public List<User> ConnectedUsers = new List<User>();

    public bool IsCurrentUserTheServer()
    {
        return CurrentUser.mUserType == UserType.SERVER;
    }

    private void Awake()
    {
        if (!Object)
        {
            Object = gameObject;
            DontDestroyOnLoad(gameObject);
        }
        else
        {
            Destroy(gameObject);
        }
    }

    public void SetLocalUser(User LocalUser)
    {
        CurrentUser = LocalUser;
    }
}
