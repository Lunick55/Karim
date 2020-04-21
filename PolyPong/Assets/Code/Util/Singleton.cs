/**
 * Singleton.cs
 * Responsible for making sure only one T object is alive at once.
 * =================================================================================================
**/

using UnityEngine;

public class Singleton<T> : MonoBehaviour where T : MonoBehaviour
{
    //private static readonly int INSTANCE_COUNT = 1;
    private static T instance;
    public static ServerCreationInfo ServerInfo;
    public static ClientConnectionInfo ClientInfo;
    public static bool IsServer = true;

    //public static T Instance
    //{
    //    get
    //    {
    //        return instance;
    //    }
    //}

    public static T Instance
    {
        get
        {
            T objOfType = FindObjectOfType<T>();

            if (!instance)
            {
                instance = objOfType;
            }
            else if (instance != objOfType)
            {
                Destroy(objOfType);
            }

            return instance;
        }
    }

    //private void Awake()
    //{
    //    //Find all T objects in the scene.
    //    T[] sceneReferences = FindObjectsOfType<T>();
    //
    //    //Set our instance if we find the required amount.
    //    //Otherwise, notify the user and set the instance to null.
    //    if (sceneReferences.Length == INSTANCE_COUNT)
    //    {
    //        instance = sceneReferences[0];
    //    }
    //    else
    //    {
    //        Debug.LogWarning(string.Format(
    //                "There should only be {0} of this object. Found: {1}", 
    //                INSTANCE_COUNT, sceneReferences.Length));
    //
    //        instance = null;
    //    }
    //}
}
