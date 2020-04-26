using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Goal : MonoBehaviour
{
    private LineRenderer GoalRenderer;
    public Vector3 GoalPostRight = Vector3.zero;
    public Vector3 GoalPostLeft = Vector3.zero;

    public void Awake()
    {
        GoalRenderer = GetComponent<LineRenderer>();
        GoalRenderer.positionCount = 2;
        GoalRenderer.numCapVertices = 0;
    }

    public void SetGoalColor(Color PlayerColor)
    {
        GoalRenderer.startColor = PlayerColor;
        GoalRenderer.endColor = PlayerColor;
    }

    public void SetGoalWidth(float Width)
    {
        GoalRenderer.startWidth = Width;
    }

    public void SetGoalPosition(Vector3 LeftGoalPost, Vector3 RightGoalPost)
    {
        GoalPostLeft = LeftGoalPost;
        GoalPostRight = RightGoalPost;

        GoalRenderer.SetPosition(0, GoalPostLeft);
        GoalRenderer.SetPosition(1, GoalPostRight);
        GetComponent<Player>().ResetPlayerPosition();
    }
}
