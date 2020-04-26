using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public struct PlayerData
{
    public int ID;
}

public class Player : MonoBehaviour
{
    //The player's user id from the server
    public int PlayerID;
    public string Username;

    public Color PlayerColor;
    public int Score;
    private Goal PlayerGoal;

    public float MinColor = 0.6f;
    public float MaxColor = 0.8f;

    [Range(0, 1)] private float AlphaAlongGoal = 0.0f;
    private float InputDirection = 0.0f;
    private float MoveSpeed = 1.0f;

    private float XScale;

    public void Awake()
    {
        InitColor();
        InitGoal();
        ResetPlayerPosition();
    }

    public void Init(int ID, string Name)
    {
        PlayerID = ID;
        Username = Name;
    }

    private void InitGoal()
    {
        PlayerGoal = GetComponent<Goal>();
        PlayerGoal.SetGoalColor(PlayerColor);
    }

    private void InitColor()
    {
        PlayerColor = GetRandomColor();
        GetComponent<SpriteRenderer>().color = PlayerColor;
    }

    private Color GetRandomColor()
    {
        return new Color(Rand(MinColor, MaxColor), Rand(MinColor, MaxColor), Rand(MinColor, MaxColor));
    }

    private float Rand(float Min, float Max)
    {
        return Random.Range(Min, Max);
    }

    public void ResetPlayerPosition()
    {
        AlphaAlongGoal = 0.5f;
        UpdatePosition();
    }

    public void FixedUpdate()
    {
        if (Input.GetKey(KeyCode.A) || Input.GetKey(KeyCode.LeftArrow))
            InputDirection = 1;
        else if (Input.GetKey(KeyCode.D) || Input.GetKey(KeyCode.RightArrow))
            InputDirection = -1;
        else
            InputDirection = 0;

        float GoalXScale = PlayerGoal.GetXScale();
        float LerpConvert = GoalXScale / PlayerGoal.GetGoalSize() * 0.5f;

        AlphaAlongGoal = Mathf.Clamp(AlphaAlongGoal + InputDirection * Time.fixedDeltaTime * MoveSpeed, LerpConvert, 1.0f - LerpConvert);
        UpdatePosition();
    }

    private void UpdatePosition()
    {
        Vector2 LerpedPosition = Vector2.Lerp(PlayerGoal.GoalPostLeft, PlayerGoal.GoalPostRight, AlphaAlongGoal);
        transform.position = LerpedPosition;

        UpdatePaddleDirection();
    }

    private void UpdatePaddleSize()
    {

    }

    //TODO: THIS DOESNT WORK WILL FIX LATER
    private void UpdatePaddleDirection()
    {
        Vector3 Direction = PlayerGoal.GoalPostLeft - PlayerGoal.GoalPostRight;

        Debug.Log(Vector2.SignedAngle(Vector3.right, Direction));
        Vector3 Rotation = transform.rotation.eulerAngles;
        transform.rotation = Quaternion.Euler(Vector3.forward * Vector2.SignedAngle(Vector3.right, Direction));
    }
}
