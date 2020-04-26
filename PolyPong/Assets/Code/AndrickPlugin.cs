using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;

public class AndrickPlugin
{
    [DllImport("AndrickPlugin")]
    public static extern int ActivateServer(int maxUsers);

    [DllImport("AndrickPlugin")]
    public static extern int ActivateClient(string ip, string username);

    [DllImport("AndrickPlugin")]
    public static extern int ShutdownNetwork();

    [DllImport("AndrickPlugin")]
    public static extern void ProcessPackets();

    [DllImport("AndrickPlugin")]
    public static extern void ExecuteEvents();

    [DllImport("AndrickPlugin")]
    public static extern void SendPackets();

    [DllImport("AndrickPlugin")]
    public static extern void CreatePacket(string packet);

    //Testing //daddy is dll
    [DllImport("AndrickPlugin")]
    public static extern Cummies FromDaddy();

    [DllImport("AndrickPlugin")]
    public static extern void ToDaddy(Cummies incuming);

}
