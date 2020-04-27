using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;

public class AndrickPlugin
{
    [DllImport("AndrickPlugin")]
    public static extern bool ActivateServer(int maxUsers);

    [DllImport("AndrickPlugin")]
    public static extern bool ActivateClient(string ip, string username);

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

    [DllImport("AndrickPlugin")]
    public static extern void CreateMessagePacket(string packet);

    [DllImport("AndrickPlugin")]
    [return: MarshalAs(UnmanagedType.LPStr)]
    public static extern string ReadMessageLog();
    
    [DllImport("AndrickPlugin")]
    [return: MarshalAs(UnmanagedType.LPStr)]
    public static extern string GetUsername();

    //Testing //daddy is dll
    [DllImport("AndrickPlugin")]
    [return: MarshalAs(UnmanagedType.LPStr)]
    public static extern string FromDaddy(string inbound);

    [DllImport("AndrickPlugin")]
    public static extern void ToDaddy(Cummies incuming);

    [DllImport("AndrickPlugin")]
    public static extern void GetPlayerData(ref PlayerData data);

    [DllImport("AndrickPlugin")]
    public static extern int GetConnectedUserCount();

    [DllImport("AndrickPlugin")]
    public static extern void GetConnectedUserId(int[] ids);
    
    [DllImport("AndrickPlugin")]
    public static extern bool DidWeConnectToServer();

    [DllImport("AndrickPlugin")]
    public static extern void DisconnectUser();
}
