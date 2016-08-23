
uniform sampler2DRect tex0; // circle image
uniform sampler2DRect tex1; // rock image
uniform sampler2DRect tex2; // rock image
uniform sampler2DRect tex3; // rock image
uniform float time;



mat2 m = mat2( 0.8,  0.6, -0.6,  0.6 );

float hash( float n )
{
    return fract(sin(n)*43758.5453);
}

float noise( in vec2 x )
{
    vec2 p = floor(x);
    vec2 f = fract(x);
    f = f*f*(3.0-2.0*f);
    float n = p.x + p.y*57.0;
    float res = mix(mix( hash(n+  0.0), hash(n+  1.0),f.x), mix( hash(n+ 57.0), hash(n+ 58.0),f.x),f.y);
    return res;
}

float fbm( vec2 p )
{
    float f = 0.0;
    f += 0.50000*noise( p ); p = m*p*2.02;
    f += 0.25000*noise( p ); p = m*p*2.03;
    f += 0.12500*noise( p ); p = m*p*2.01;
    f += 0.06250*noise( p ); p = m*p*2.04;
    f += 0.03125*noise( p );
    return f/0.984375;
}



void main(void)
{
    vec2 st = gl_TexCoord[0].st;
    vec2 stOrig = st;
    
    float noiseScale = 0.02;
    vec2 coord = vec2(gl_FragCoord.x*noiseScale + time*0.2, gl_FragCoord.y*noiseScale);
    float fx = fbm(coord);
    
    vec2 coord2 = vec2(gl_FragCoord.y*noiseScale + 10000.0 - time*0.2, gl_FragCoord.x*noiseScale);
    float fy = fbm(coord2);
    
    
    
    //st *= vec2(0.1, 0.1);  // zooms in on the rock texture
    
    vec2 coordA = vec2(st*(1.93 -0.1 * sin(time*0.7)));
    vec2 coordB = vec2(st*(1.93-0.1 * sin(time)));
    
    coordA.x = mod(coordA.x, 2000.0);
    coordA.y = mod(coordA.y, 2000.0);
    coordB.x = mod(coordB.x, 2000.0);
    coordB.y = mod(coordB.y, 2000.0);
    
    vec4 col = texture2DRect(tex3,coordA);
    vec4 col2 = texture2DRect(tex3,coordB);
    
    
    // 5 = how much displacement, try 50 or 100, etc.  always use decimal nums (10.0, etc)
    vec2 st2 = stOrig + vec2(fx-0.5 + sin(time*0.7 + gl_FragCoord.y*0.01)*0.2, fy-0.3)*8.0 + (3.0) *  vec2(col.x-0.45, col2.x-0.35);
    vec4 color2 = texture2DRect(tex0, st2);
    
	gl_FragColor = vec4(color2.x, color2.y, color2.z, 1.0);
}