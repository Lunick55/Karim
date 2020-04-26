using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;

public class AndrickPlugin
{
    [DllImport("AndrickPlugin")]
    public static extern int ActivateServer(int maxUsers);

    [DllImport("AndrickPlugin")]
    public static extern bool TestMeDaddy();

    [DllImport("AndrickPlugin")]
    public static extern int ActivateClient(string ip);

    [DllImport("AndrickPlugin")]
    public static extern int ShutdownNetwork();

    [DllImport("AndrickPlugin")]
    public static extern void UpdateClient();

    [DllImport("AndrickPlugin")]
    public static extern void UpdateServer();

}
