using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public struct PlayerData
{
    public int ID;
}

public class Player : MonoBehaviour
{
    public PlayerInfo PlayerData;

    public Color PlayerColor;
    public int Score;
    private Goal PlayerGoal;

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

    public void Init(PlayerInfo Info)
    {
        PlayerData = Info;
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
        Color C = Random.ColorHSV(0.0f, 1.0f, 0.3f, 0.5f, 0.8f, 1f);
        C.r += 0.1f;//ColorHSV leans toward green/blue for some reason.
        return C;// new Color(Rand(MinColor, MaxColor), Rand(MinColor, MaxColor), Rand(MinColor, MaxColor));
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
        //if (IsLocallyControlled)
            UpdateLocalPaddleMovement();
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

    public void UpdateRemotePaddleMovement(float Alpha)
    {
        if (!PlayerData.IsLocallyControlled)
        {
            float GoalXScale = PlayerGoal.GetXScale();
            float LerpConvert = GoalXScale / PlayerGoal.GetGoalSize() * 0.5f;

            AlphaAlongGoal = Alpha;
            UpdatePosition();
        }
    }

    public void UpdateLocalPaddleMovement()
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

        //Send new alpha to DLL
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
