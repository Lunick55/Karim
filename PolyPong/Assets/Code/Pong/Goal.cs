using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Goal : MonoBehaviour
{
    private LineRenderer GoalRenderer;
    public Vector3 GoalPostRight = Vector3.zero;
    public Vector3 GoalPostLeft = Vector3.zero;

    private Vector3 GoalPostRightVisualPosition = Vector3.zero;
    private Vector3 GoalPostLeftVisualPosition = Vector3.zero;

    public float GoalColorAlphaScale = 0.5f;
    public int GoalIndices = 30;
    public int CapIndices = 10;
    public float GoalWidthScale = 0.8f;

    public float GoalSizeMagnitude;

    public void Awake()
    {
        GoalRenderer = GetComponent<LineRenderer>();
        GoalRenderer.positionCount = GoalIndices;
        GoalRenderer.numCapVertices = CapIndices;
        GoalSizeMagnitude = 0.0f;
    }

    public void SetGoalColor(Color PlayerColor)
    {
        Gradient gradient = new Gradient();
        gradient.SetKeys(
            new GradientColorKey[] { 
                new GradientColorKey(PlayerColor, 0.0f), 
                new GradientColorKey(PlayerColor, 1.0f) },
            
            new GradientAlphaKey[] {
                new GradientAlphaKey(0.8f, 0.0f),
                new GradientAlphaKey(0.93f, 0.4f),
                new GradientAlphaKey(0.95f, 0.5f),
                new GradientAlphaKey(0.93f, 0.6f),
                new GradientAlphaKey(0.8f, 1.0f)
            }
        );

        GoalRenderer.colorGradient = gradient;
    }

    public void SetGoalThickness(float Thickness)
    {
        GoalRenderer.startWidth = Thickness;
        GoalRenderer.endWidth = Thickness;
    }

    private void SetGoalWidthScale()
    {
        Vector3 Middle = (GoalPostLeft + GoalPostRight) * 0.5f;
        Vector3 LeftDir = (GoalPostLeft - Middle) * GoalWidthScale;
        Vector3 RightDir = (GoalPostRight - Middle) * GoalWidthScale;

        GoalPostLeftVisualPosition = Middle + LeftDir;
        GoalPostRightVisualPosition = Middle + RightDir;
    }

    public float GetXScale()
    {
        return GoalSizeMagnitude * 0.4f;
    }

    public float GetGoalSize()
    {
        return GoalSizeMagnitude;
    }

    public void SetGoalPosition(Vector3 LeftGoalPost, Vector3 RightGoalPost)
    {
        GoalPostLeft = LeftGoalPost;
        GoalPostRight = RightGoalPost;
        GoalSizeMagnitude = (GoalPostLeft - GoalPostRight).magnitude;

        SetGoalWidthScale();
        UpdatePositions();
        GetComponent<Player>().ResetPlayerPosition();
    }

    private void UpdatePositions()
    {
        float DistBetween = (GoalSizeMagnitude * GoalWidthScale) / GoalIndices;
        Vector3 DistVec = (GoalPostRightVisualPosition - GoalPostLeftVisualPosition).normalized * DistBetween;

        for (int i = 0; i < GoalIndices; ++i)
            GoalRenderer.SetPosition(i, GoalPostLeftVisualPosition + (DistVec * i));
    }
}
