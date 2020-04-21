using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class SceneTracker : MonoBehaviour
{
    public void LoadSceneSynchronously(SceneInfo info)
    {
        SceneManager.LoadScene(info.sceneID, LoadSceneMode.Single);
    }

    public AsyncOperation LoadSceneAsync(
        SceneInfo info, LoadSceneMode mode = LoadSceneMode.Additive,
        Func<AsyncOperation, IEnumerator> loadHandler = null)
    {
        //if (info.sceneType == SceneType.FULLSCREEN)
        //{
        //    Debug.Log(string.Format("Adding fullscreen scene: {0} to history.", info.sceneID));
        //    mSceneHistory.Push(info);
        //}

        AsyncOperation loadOperation = SceneManager.LoadSceneAsync(info.sceneID, mode);

        if (loadHandler != null)
        {
            StartCoroutine(loadHandler(loadOperation));
        }

        return loadOperation;
    }

    public AsyncOperation UnloadSceneAsync(
        SceneInfo info, Func<AsyncOperation, IEnumerator> unloadHandler = null)
    {
        AsyncOperation unloadOperation = SceneManager.UnloadSceneAsync(info.sceneID,
            UnloadSceneOptions.UnloadAllEmbeddedSceneObjects);

        //Debug.Log(string.Format("Unloading scene with id: {0} to history.", sceneID));

        if (unloadHandler != null)
        {
            StartCoroutine(unloadHandler(unloadOperation));
        }

        return unloadOperation;
    }
}
