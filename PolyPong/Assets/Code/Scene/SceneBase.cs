using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class SceneBase<T> : Singleton<T> where T : Singleton<T>
{
    private static GameObject persistenceInstance;

    public GameObject GetPersistentTracker()
    {
        if (!persistenceInstance)
        {
            persistenceInstance = Instantiate(Resources.Load<GameObject>("Prefab/Persistent/POLY_PONG_CORE"));
            persistenceInstance.name = "POLY_PONG_CORE";
        }

        return persistenceInstance;
    }

    public SceneTracker GetSceneTracker()
    {
        return GetPersistentTracker().GetComponent<SceneTracker>();
    }

    public void OnQuitPressed()
    {
        Application.Quit();
    }

    public void OnMainMenuPressed()
    {
        GetSceneTracker().LoadSceneSynchronously(SceneInfoList.TITLE_MENU);
    }

    public void OnJoinLobbyClient()
    {
        //Send over the necessary info to the server.
        GetSceneTracker().LoadSceneSynchronously(SceneInfoList.LOBBY_CLIENT);
    }

    public void OnJoinLobbyServer()
    {
        GetSceneTracker().LoadSceneSynchronously(SceneInfoList.LOBBY_SERVER);
    }
}
