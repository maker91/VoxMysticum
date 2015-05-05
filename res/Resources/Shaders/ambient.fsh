uniform sampler2D texture;
uniform vec4 ambient;

void main()
{
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    gl_FragColor = vec4(ambient.rgb, pixel.a*ambient.a);
}