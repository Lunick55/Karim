using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Persistent : Singleton<Persistent>
{
    public static GameObject instance;

    public List<PlayerInfo> ConnectedPlayers = new List<PlayerInfo>();
    public ServerCreationInfo ServerInfo;
    public ClientConnectionInfo ClientInfo;

    public bool isServer;

    private void Awake()
    {
        if (!instance)
        {
            instance = gameObject;
            DontDestroyOnLoad(gameObject);
        }
        else
        {
            //Destroy(gameObject);
        }
    }
}
