#version 300 es

precision mediump float;

in vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
in vec2 vTexCoords; // Coordonnées de texture du sommet

uniform sampler2D uTexture;

out vec3 fColor;

void main(){
    vec4 sortie = texture(uTexture, vTexCoords);
    fColor = vec3(sortie);
    //normalize(vNormal_vs);
    //fColor = vNormal_vs;
}
