﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Persistent : MonoBehaviour
{
    public static GameObject instance;

    public List<Player> ConnectedPlayers = new List<Player>();

    private void Awake()
    {
        if (!instance)
        {
            instance = gameObject;
            DontDestroyOnLoad(gameObject);
        }
        else
        {
            Destroy(gameObject);
        }
    }
}
