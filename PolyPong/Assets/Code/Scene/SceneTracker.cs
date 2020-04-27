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
        AsyncOperation loadOperation = SceneManager.LoadSceneAsync(info.sceneID, mode);

        if (loadHandler != null)
            StartCoroutine(loadHandler(loadOperation));

        return loadOperation;
    }

    public AsyncOperation UnloadSceneAsync(
        SceneInfo info, Func<AsyncOperation, IEnumerator> unloadHandler = null)
    {
        AsyncOperation unloadOperation = SceneManager.UnloadSceneAsync(info.sceneID,
            UnloadSceneOptions.UnloadAllEmbeddedSceneObjects);

        if (unloadHandler != null)
            StartCoroutine(unloadHandler(unloadOperation));

        return unloadOperation;
    }
}
