uniform sampler2D texture;
uniform float x;
uniform float y;
uniform float z;

void main()
{
	vec2 resolution = vec2(1280, 720);
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy * x);
	vec2 coord = gl_FragCoord.xy / resolution;

	vec4 color = vec4(x, y, z, 1);
	color.r += sin(coord.x * 90.0);
	color.g += cos(coord.y * 90.0);

    gl_FragColor =  color * pixel;	
}
