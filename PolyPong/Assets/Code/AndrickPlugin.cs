using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;

public class AndrickPlugin
{
    [DllImport("AndrickPlugin")]
    public static extern void ActivateServer();

    [DllImport("AndrickPlugin")]
    public static extern bool TestMeDaddy();

    

}
