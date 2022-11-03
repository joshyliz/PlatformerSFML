uniform sampler2D texture;
uniform float z;

void main()
{
	vec2 resolution = vec2(1280 * 0.5, 720 * 0.5);
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	vec2 coord = gl_FragCoord.xy / resolution;
	
	float color = 0.0;

	color += sin(coord.x * 50.0 + cos(z + coord.y * 10.0 + sin(coord.x * 50.0 + z 
	* 2.0))) * 2.0;
	color += sin(coord.x * 20.0 + cos(z + coord.y * 10.0 + sin(coord.x * 50.0 + z 
	* 2.0))) * 2.0;
	color += sin(coord.x * 30.0 + cos(z + coord.y * 10.0 + sin(coord.x * 50.0 + z 
	* 2.0))) * 2.0;
	color += sin(coord.x * 10.0 + cos(z + coord.y * 10.0 + sin(coord.x * 50.0 + z 
	* 2.0))) * 2.0;

    gl_FragColor =  vec4(vec3(color + coord.y + 10.0, color * 0.25, 0), 1.0) * pixel;	
}
