/**
 * CameraResizer.cs
 * Resizes the camera to fit the desired game pixel resolution.
 * =================================================================================================
**/

using UnityEngine;

public class CameraResizer : MonoBehaviour
{
    private static readonly Vector2 GAME_RESOLUTION = new Vector2(960, 540);
    private Camera mCamera;

    private void Awake()
    {
        OnValidate();
    }

    private void OnValidate()
    {
        mCamera = GetComponent<Camera>();
        CalculateCameraSize();
    }

    private void CalculateCameraSize()
    {
        if (mCamera.orthographic)
        {
            mCamera.orthographicSize = 0.5f * GAME_RESOLUTION.y;
        }
    }
}
