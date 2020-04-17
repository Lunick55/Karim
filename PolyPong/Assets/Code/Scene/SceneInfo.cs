using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum SceneType
{
    BACKGROUND_TASK,
    OVERLAY,
    FULLSCREEN
}

public struct SceneInfo
{
    public readonly SceneType sceneType;
    public readonly string sceneID;

    public SceneInfo(string ID, SceneType type)
    {
        sceneID = ID; 
        sceneType = type;
    }
}
