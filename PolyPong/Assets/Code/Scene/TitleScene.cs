using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TitleScene : SceneBase<TitleScene>
{
    public void OnCreateServerPressed()
    {
        GetPersistentTracker().GetComponent<SceneTracker>().LoadSceneSynchronously(SceneInfoList.CREATE_SERVER);
    }

    public void OnJoinServerPressed()
    {
        GetPersistentTracker().GetComponent<SceneTracker>().LoadSceneSynchronously(SceneInfoList.JOIN_SERVER);
    }
}
