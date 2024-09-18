//定数バッファ(メッシュ単位)
cbuffer cbMesh:register(b1)
{
	//オブジェクト情報
	row_major float4x4 g_mWorld;	//ワールド変換行列
}

cbuffer cdMaterial : register(b2)
{
	float4 g_BaseColor;//ベース色
	float3 g_Emissive;//自己発行色
	float3 g_Materic;//金属度
	float3 g_Roughness;//荒さ
}

//頂点シェーダーから出力するデータ
struct VSOutput
{
	float4 Pos : SV_Position;
	float2 UV : TEXCOORD1;
	float4 Color : TEXCOORD2;
};
